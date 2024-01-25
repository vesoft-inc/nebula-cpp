/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/Init.h>
#include <common/datatypes/DataSet.h>
#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Session.h>
#include <nebula/mclient/MetaClient.h>
#include <nebula/sclient/ScanEdgeIter.h>
#include <nebula/sclient/StorageClient.h>

#include "./SClientTest.h"

// Require a nebula server could access

#define kServerHost "127.0.0.1"

class StorageClientTest : public SClientTest {
 protected:
  static void prepare() {
    nebula::ConnectionPool pool;
    pool.init({kServerHost ":9669"}, nebula::Config{0, 0, 10, 0, "", true});
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());
    EXPECT_TRUE(session.ping());
    auto result = session.execute(
        "CREATE SPACE IF NOT EXISTS storage_client_test(vid_type=FIXED_STRING(8),"
        "partition_num=1);USE storage_client_test");
    ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED) << *result.errorMsg;

    auto result2 = session.execute(
        "CREATE EDGE IF NOT EXISTS like(likeness int);"
        "CREATE TAG IF NOT EXISTS player(name string);");
    ASSERT_EQ(result2.errorCode, nebula::ErrorCode::SUCCEEDED) << *result2.errorMsg;

    ::sleep(30);

    auto result3 = session.execute(
        "INSERT EDGE like(likeness) VALUES '101'->'102':(78), '102'->'103':(99), "
        "'103'->'201':(43), '201'->'202':(56), '202'->'203':(-13), '203'->'301':(431), "
        "'301'->'302':(457)");
    ASSERT_EQ(result3.errorCode, nebula::ErrorCode::SUCCEEDED)
        << (result3.errorMsg ? *result3.errorMsg : "");

    auto result4 = session.execute(
        "INSERT VERTEX player(name) VALUES 'Tim':('Tim'), 'Bob':('Bob'), "
        "'Alice':('Alice'), 'Tifa':('Tifa'), 'Mario':('Mario'), 'Jack':('Jack'), "
        "'Tom':('Tom')");
    ASSERT_EQ(result4.errorCode, nebula::ErrorCode::SUCCEEDED)
        << (result4.errorMsg ? *result4.errorMsg : "");
  }

  static void runOnce(nebula::MetaClient &c) {
    auto ret = c.getSpaceIdByNameFromCache("storage_client_test");
    ASSERT_TRUE(ret.first);
    nebula::GraphSpaceID spaceId = ret.second;
    LOG(INFO) << "spaceId of nba: " << spaceId;
    EXPECT_GT(spaceId, 0);

    auto ret2 = c.getEdgeTypeByNameFromCache(spaceId, "like");
    ASSERT_TRUE(ret2.first);
    nebula::EdgeType edgeType = ret2.second;
    LOG(INFO) << "edgeType of like: " << edgeType;
    EXPECT_GT(edgeType, 0);

    auto ret3 = c.getPartsFromCache(spaceId);
    ASSERT_TRUE(ret3.first);
    auto parts = ret3.second;
    EXPECT_EQ(parts, (std::vector<nebula::PartitionID>{1}));

    auto ret4 = c.getPartLeaderFromCache(spaceId, 1);
    ASSERT_TRUE(ret4.first);
    EXPECT_EQ(ret4.second, nebula::HostAddr(kServerHost, 9779));
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
        std::pair<nebula::ErrorCode, nebula::DataSet> res = goodScanIter.next();
        EXPECT_EQ(res.first, nebula::ErrorCode::SUCCEEDED);
        got.append(std::move(res.second));
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
        std::pair<nebula::ErrorCode, nebula::DataSet> res = badScanIter.next();
        EXPECT_NE(res.first, nebula::ErrorCode::SUCCEEDED);
        EXPECT_EQ(res.second, nebula::DataSet());
        EXPECT_EQ(badScanIter.hasNext_, false);
        EXPECT_EQ(badScanIter.nextCursor_, "");
      }
    }
  }

  static void runScanVertexWithPart(nebula::StorageClient &c) {
    LOG(INFO) << "run with goodScanIter";
    {
      auto goodScanIter = c.scanVertexWithPart("storage_client_test",
                                               1,
                                               {{"player", {"name"}}},
                                               3,
                                               0,
                                               std::numeric_limits<int64_t>::max(),
                                               "",
                                               true,
                                               true);
      nebula::DataSet expected({"_vid", "player.name"});
      expected.emplace_back(nebula::List({"Alice", "Alice"}));
      expected.emplace_back(nebula::List({"Bob", "Bob"}));
      expected.emplace_back(nebula::List({"Jack", "Jack"}));
      expected.emplace_back(nebula::List({"Mario", "Mario"}));
      expected.emplace_back(nebula::List({"Tifa", "Tifa"}));
      expected.emplace_back(nebula::List({"Tim", "Tim"}));
      expected.emplace_back(nebula::List({"Tom", "Tom"}));

      nebula::DataSet got;
      int scanNum = 0;
      while (goodScanIter.hasNext()) {
        std::pair<nebula::ErrorCode, nebula::DataSet> res = goodScanIter.next();
        got.append(std::move(res.second));
        ++scanNum;
      }
      EXPECT_EQ(scanNum, 3);
      DLOG(ERROR) << "DEBUG POINT: " << got;
      EXPECT_TRUE(verifyResultWithoutOrder(got, expected));
    }
    LOG(INFO) << "run with badScanIter";
    {
      auto badScanIter = c.scanVertexWithPart("storage_client_test",
                                              999,  // non-existent partId
                                              {{"player", {"name"}}},
                                              10,
                                              0,
                                              std::numeric_limits<int64_t>::max(),
                                              "",
                                              true,
                                              true);
      {
        EXPECT_EQ(badScanIter.hasNext(), true);
        std::pair<nebula::ErrorCode, nebula::DataSet> res = badScanIter.next();
        EXPECT_NE(res.first, nebula::ErrorCode::SUCCEEDED);
        EXPECT_EQ(res.second, nebula::DataSet());
        EXPECT_EQ(badScanIter.hasNext_, false);
        EXPECT_EQ(badScanIter.nextCursor_, "");
      }
    }
  }
};

TEST_F(StorageClientTest, SSL) {
  LOG(INFO) << "Prepare data.";
  prepare();
  nebula::MConfig mConfig{1000, 60 * 1000, true, ""};
  nebula::SConfig sConfig{1000, 60 * 1000, true, ""};
  nebula::StorageClient c({kServerHost ":9559"}, mConfig, sConfig);
  auto *m = c.getMetaClient();
  LOG(INFO) << "Testing run once of meta client";
  runOnce(*m);
  LOG(INFO) << "Testing run get parts.";
  runGetParts(c);
  LOG(INFO) << "Testing run scan edge with part.";
  runScanEdgeWithPart(c);
  LOG(INFO) << "Testing run scan vertex with part.";
  runScanVertexWithPart(c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
