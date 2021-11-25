/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/datatypes/DataSet.h>
#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Session.h>
#include <nebula/mclient/MetaClient.h>
#include <nebula/sclient/Init.h>
#include <nebula/sclient/ScanEdgeIter.h>
#include <nebula/sclient/StorageClient.h>

#include "../../ClientTest.h"

// Require a nebula server could access

#define kServerHost "127.0.0.1"

class StorageClientTest : public ClientTest {
 protected:
  static void prepare() {
    nebula::ConnectionPool pool;
    pool.init({kServerHost ":9669"}, nebula::Config{});
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());
    EXPECT_TRUE(session.ping());
    auto result = session.execute(
        "CREATE SPACE IF NOT EXISTS storage_client_test(vid_type=FIXED_STRING(8),"
        "partition_num=1);USE storage_client_test");
    ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);

    auto result2 = session.execute("CREATE EDGE IF NOT EXISTS like(likeness int)");
    ASSERT_EQ(result2.errorCode, nebula::ErrorCode::SUCCEEDED);

    ::sleep(10);

    auto result3 = session.execute(
        "INSERT EDGE like(likeness) VALUES '101'->'102':(78), '102'->'103':(99), "
        "'103'->'201':(43), '201'->'202':(56), '202'->'203':(-13), '203'->'301':(431), "
        "'301'->'302':(457)");
    ASSERT_EQ(result3.errorCode, nebula::ErrorCode::SUCCEEDED)
        << (result2.errorMsg ? *result2.errorMsg : "");

    ::sleep(10);
  }

  static void runGetParts(nebula::StorageClient &c) {
    auto parts = c.getParts("storage_client_test");
    EXPECT_EQ(parts, (std::vector<nebula::PartitionID>{1}));
  }

  static void runScanEdgeWithPart(nebula::StorageClient &c) {
    LOG(INFO) << "run with goodScanIter";
    {
      auto goodScanIter = c.scanEdgeWithPart("storage_client_test",
                                             1,
                                             "like",
                                             std::vector<std::string>{"likeness"},
                                             3,
                                             0,
                                             std::numeric_limits<int64_t>::max(),
                                             "",
                                             true,
                                             true);
      nebula::DataSet expected({"like.likeness"});
      expected.emplace_back(nebula::List({78}));
      expected.emplace_back(nebula::List({99}));
      expected.emplace_back(nebula::List({43}));
      expected.emplace_back(nebula::List({56}));
      expected.emplace_back(nebula::List({-13}));
      expected.emplace_back(nebula::List({431}));
      expected.emplace_back(nebula::List({457}));

      nebula::DataSet got;
      int scanNum = 0;
      while (goodScanIter.hasNext()) {
        nebula::DataSet ds = goodScanIter.next();
        got.append(std::move(ds));
        ++scanNum;
      }
      EXPECT_EQ(scanNum, 3);
      EXPECT_TRUE(verifyResultWithoutOrder(got, expected));
    }
    LOG(INFO) << "run with badScanIter";
    {
      auto badScanIter = c.scanEdgeWithPart("storage_client_test",
                                            999,  // non-existent partId
                                            "like",
                                            std::vector<std::string>(),
                                            10,
                                            0,
                                            std::numeric_limits<int64_t>::max(),
                                            "",
                                            true,
                                            true);
      {
        EXPECT_EQ(badScanIter.hasNext(), true);
        nebula::DataSet ds = badScanIter.next();
        EXPECT_EQ(ds, nebula::DataSet());
        EXPECT_EQ(badScanIter.hasNext_, false);
        EXPECT_EQ(badScanIter.nextCursor_, "");
      }
    }
  }
};

TEST_F(StorageClientTest, Basic) {
  LOG(INFO) << "Prepare data.";
  prepare();
  nebula::StorageClient c({kServerHost ":9559"});
  LOG(INFO) << "Testing run get parts.";
  runGetParts(c);
  LOG(INFO) << "Testing run scan edge with part.";
  runScanEdgeWithPart(c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
