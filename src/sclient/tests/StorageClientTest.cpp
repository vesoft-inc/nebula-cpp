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
    pool.init({kServerHost ":9669"}, nebula::Config{});
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());
    EXPECT_TRUE(session.ping());
    auto result = session.execute(
        "CREATE SPACE IF NOT EXISTS storage_client_test(vid_type=FIXED_STRING(8),"
        "partition_num=1);USE storage_client_test");
    ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);

    auto result2 = session.execute(
        "CREATE EDGE IF NOT EXISTS like(likeness int);"
        "CREATE EDGE IF NOT EXISTS follow(rank1 int, rank2 int);"
        "CREATE TAG IF NOT EXISTS player(name string);");
    ASSERT_EQ(result2.errorCode, nebula::ErrorCode::SUCCEEDED);

    ::sleep(30);

    auto result3 = session.execute(
        "INSERT EDGE like(likeness) VALUES '101'->'102':(78), '102'->'103':(99), "
        "'103'->'201':(43), '201'->'202':(56), '202'->'203':(-13), '203'->'301':(431), "
        "'301'->'302':(457)");
    ASSERT_EQ(result3.errorCode, nebula::ErrorCode::SUCCEEDED)
        << (result3.errorMsg ? *result3.errorMsg : "");

    auto result4 = session.execute(
        "INSERT EDGE follow(rank1, rank2) VALUES '101'->'102':(1, 100), '102'->'103':(2, 200), "
        "'103'->'201':(3, 300), '201'->'202':(4, 400), '202'->'203':(5, 500), '203'->'301':(6, "
        "600), "
        "'301'->'302':(7, 700)");
    ASSERT_EQ(result4.errorCode, nebula::ErrorCode::SUCCEEDED)
        << (result4.errorMsg ? *result4.errorMsg : "");

    auto resul5 = session.execute(
        "INSERT VERTEX player(name) VALUES 'Tim':('Tim'), 'Bob':('Bob'), "
        "'Alice':('Alice'), 'Tifa':('Tifa'), 'Mario':('Mario'), 'Jack':('Jack'), "
        "'Tom':('Tom')");
    ASSERT_EQ(resul5.errorCode, nebula::ErrorCode::SUCCEEDED)
        << (resul5.errorMsg ? *resul5.errorMsg : "");
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
        nebula::DataSet ds = goodScanIter.next();
        got.append(std::move(ds));
        ++scanNum;
      }
      EXPECT_EQ(scanNum, 3);
      EXPECT_TRUE(verifyResultWithoutOrder(got, expected));
    }

    LOG(INFO) << "run with goodScanIter";
    {
      auto goodScanIter = c.scanEdgeWithPart(
          "storage_client_test",
          1,
          {{"like", std::vector<std::string>{"_src", "_dst", "likeness"}},
           {"follow", std::vector<std::string>{"_src", "_dst", "rank1", "rank2"}}},
          3,
          0,
          std::numeric_limits<int64_t>::max(),
          "",
          true,
          true);
      nebula::DataSet got;
      while (goodScanIter.hasNext()) {
        nebula::DataSet ds = goodScanIter.next();
        got.append(std::move(ds));
      }

      EXPECT_EQ(got.rows[0], nebula::List({"101", "102", 78}));
      EXPECT_EQ(got.rows[1], nebula::List({"101", "102", 1, 100}));

      EXPECT_EQ(got.rows[2], nebula::List({"102", "103", 99}));
      EXPECT_EQ(got.rows[3], nebula::List({"102", "103", 2, 200}));

      EXPECT_EQ(got.rows[4], nebula::List({"103", "201", 43}));
      EXPECT_EQ(got.rows[5], nebula::List({"103", "201", 3, 300}));

      EXPECT_EQ(got.rows[6], nebula::List({"201", "202", 56}));
      EXPECT_EQ(got.rows[7], nebula::List({"201", "202", 4, 400}));

      EXPECT_EQ(got.rows[8], nebula::List({"202", "203", -13}));
      EXPECT_EQ(got.rows[9], nebula::List({"202", "203", 5, 500}));

      EXPECT_EQ(got.rows[10], nebula::List({"203", "301", 431}));
      EXPECT_EQ(got.rows[11], nebula::List({"203", "301", 6, 600}));

      EXPECT_EQ(got.rows[12], nebula::List({"301", "302", 457}));
      EXPECT_EQ(got.rows[13], nebula::List({"301", "302", 7, 700}));
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
        nebula::DataSet ds = goodScanIter.next();
        got.append(std::move(ds));
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
