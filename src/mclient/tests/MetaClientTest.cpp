/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <nebula/mclient/MetaClient.h>
#include <nebula/sclient/Init.h>

#include "../../ClientTest.h"
#include "common/datatypes/HostAddr.h"
#include "common/thrift/ThriftTypes.h"

// Require a nebula server could access

#define kServerHost "127.0.0.1"

class MetaClientTest : public ClientTest {
 protected:
  static void runOnce(nebula::MetaClient &c) {
    auto ret = c.getSpaceIdByNameFromCache("nba");
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
    LOG(INFO) << "parts id: ";
    for (auto partId : parts) {
      LOG(INFO) << partId << ",";
    }
    EXPECT_GT(parts.size(), 0);

    auto ret4 = c.getPartLeaderFromCache(spaceId, 1);
    ASSERT_TRUE(ret4.first);
    EXPECT_EQ(ret4.second, nebula::HostAddr("127.0.0.1", 48856));
  }
};

TEST_F(MetaClientTest, Basic) {
  nebula::MetaClient c({kServerHost ":45996"});
  runOnce(c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
