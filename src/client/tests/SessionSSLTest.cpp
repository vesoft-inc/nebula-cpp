/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/Init.h>
#include <common/datatypes/Geography.h>
#include <folly/json.h>
#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Session.h>

#include <atomic>
#include <chrono>
#include <thread>

#include "./ClientTest.h"

// Require a nebula server could access

#define kServerHost "graphd"

class SessionTest : public ClientTest {};

TEST_F(SessionTest, SSL) {
  nebula::ConnectionPool pool;
  nebula::Config c{10, 0, 10, 0, "", true};
  pool.init({kServerHost ":9669"}, c);
  auto session = pool.getSession("root", "nebula");
  ASSERT_TRUE(session.valid());

  // execute
  auto result = session.execute("YIELD 1");
  ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
  nebula::DataSet expected({"1"});
  expected.emplace_back(nebula::List({1}));
  EXPECT_TRUE(verifyResultWithoutOrder(*result.data, expected));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
