/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/Init.h>
#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Session.h>
#include <nebula/mclient/MetaClient.h>

#include "./MClientTest.h"
#include "common/datatypes/HostAddr.h"
#include "common/thrift/ThriftTypes.h"

// Require a nebula server could access

#define kServerHost "127.0.0.1"

class MetaClientTest : public MClientTest {
 protected:
  static void prepare() {
    nebula::ConnectionPool pool;
    pool.init({kServerHost ":9669"}, nebula::Config{});
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());
    EXPECT_TRUE(session.ping());
    auto result = session.execute(
        "CREATE SPACE IF NOT EXISTS meta_client_test(vid_type=FIXED_STRING(8),"
        "partition_num=3);USE meta_client_test");
    ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);

    auto result2 = session.execute("CREATE EDGE IF NOT EXISTS like(likeness int)");
    ASSERT_EQ(result2.errorCode, nebula::ErrorCode::SUCCEEDED);

    ::sleep(30);

    auto result3 = session.execute(
        "INSERT EDGE like(likeness) VALUES '101'->'102':(78), '102'->'103':(99), "
        "'103'->'201':(43), '201'->'202':(56), '202'->'203':(-13), '203'->'301':(431), "
        "'301'->'302':(457)");
    ASSERT_EQ(result3.errorCode, nebula::ErrorCode::SUCCEEDED);
  }

  static void runOnce(nebula::MetaClient &c) {
    auto ret = c.getSpaceIdByNameFromCache("meta_client_test");
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
    EXPECT_EQ(parts, (std::vector<nebula::PartitionID>{1, 2, 3}));

    auto ret4 = c.getPartLeaderFromCache(spaceId, 1);
    ASSERT_TRUE(ret4.first);
    EXPECT_EQ(ret4.second, nebula::HostAddr(kServerHost, 9779));
  }
};

TEST_F(MetaClientTest, Basic) {
  LOG(INFO) << "Prepare data.";
  prepare();

  LOG(INFO) << "Run once.";
  nebula::MetaClient c({kServerHost ":9559"});
  runOnce(c);
}

TEST_F(MetaClientTest, SSL) {
  LOG(INFO) << "Prepare data.";
  prepare();

  LOG(INFO) << "Run once.";
  nebula::MConfig mConfig{1000, 60*1000, true, ""};
  nebula::MetaClient c({kServerHost ":9559"}, mConfig);
  runOnce(c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
