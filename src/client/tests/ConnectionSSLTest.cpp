/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/Init.h>
#include <folly/json.h>
#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <nebula/client/Connection.h>

#include "./ClientTest.h"

// Require a nebula server could access

static constexpr char kServerHost[] = "graphd";

class ConnectionTest : public ClientTest {};

TEST_F(ConnectionTest, SSL) {
  nebula::Connection c;

  ASSERT_TRUE(c.open(kServerHost, 9669, 10, true, ""));

  // auth
  auto authResp = c.authenticate("root", "nebula");
  ASSERT_EQ(authResp.errorCode, nebula::ErrorCode::SUCCEEDED) << *authResp.errorMsg;

  // execute
  auto resp = c.execute(*authResp.sessionId, "YIELD 1");
  ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
  nebula::DataSet expected({"1"});
  expected.emplace_back(nebula::List({1}));
  EXPECT_TRUE(verifyResultWithoutOrder(*resp.data, expected));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
