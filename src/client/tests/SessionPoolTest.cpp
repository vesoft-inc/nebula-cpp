// Copyright (c) 2022 vesoft inc. All rights reserved.
//
// This source code is licensed under Apache 2.0 License.

#include <common/Init.h>
#include <common/datatypes/Geography.h>
#include <folly/json.h>
#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <nebula/client/SessionPool.h>

#include <atomic>
#include <chrono>
#include <thread>

#include "./ClientTest.h"

// Require a nebula server could access

#define kServerHost "graphd"

class SessionPoolTest : public ClientTest {
 protected:
  void SetUp() {
    nebula::ConnectionPool pool;
    pool.init({kServerHost ":9669"}, nebula::Config{0, 0, 1, 0, "", false});
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());

    auto resp = session.execute(
        "CREATE SPACE IF NOT EXISTS session_pool_test(vid_type = FIXED_STRING(16));"
        "CREATE SPACE IF NOT EXISTS session_pool_test2(vid_type = FIXED_STRING(16));");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;
    ::sleep(20);  // wait schema sync
  }

  void TearDown() {
    nebula::ConnectionPool pool;
    pool.init({kServerHost ":9669"}, nebula::Config{0, 0, 1, 0, "", false});
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());

    auto resp = session.execute("DROP SPACE session_pool_test;DROP SPACE session_pool_test2;");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;
  }
};

TEST_F(SessionPoolTest, Basic) {
  nebula::SessionPoolConfig config;
  config.username_ = "root";
  config.password_ = "nebula";
  config.addrs_ = {kServerHost ":9669"};
  config.spaceName_ = "session_pool_test";
  config.maxSize_ = 10;
  nebula::SessionPool pool(config);
  pool.init();

  std::vector<std::thread> threads;
  for (std::size_t i = 0; i < config.maxSize_; ++i) {
    threads.emplace_back([&pool]() {
      // using namespace std::chrono_literals;  // NOLINT
      // std::this_thread::sleep_for(1s);

      auto resp = pool.execute("YIELD 1");
      ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;
      nebula::DataSet expected({"1"});
      expected.emplace_back(nebula::Row({1}));
      ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    });
  }
  for (auto& t : threads) {
    t.join();
  }
}

TEST_F(SessionPoolTest, SwitchSpace) {
  nebula::SessionPoolConfig config;
  config.username_ = "root";
  config.password_ = "nebula";
  config.addrs_ = {kServerHost ":9669"};
  config.spaceName_ = "session_pool_test";
  config.maxSize_ = 10;
  nebula::SessionPool pool(config);
  pool.init();

  std::vector<std::thread> threads;
  for (std::size_t i = 0; i < config.maxSize_; ++i) {
    threads.emplace_back([&pool]() {
      // using namespace std::chrono_literals;  // NOLINT
      // std::this_thread::sleep_for(1s);

      auto resp = pool.execute("USE session_pool_test2");
      ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

      resp = pool.execute("YIELD 1");
      nebula::DataSet expected({"1"});
      expected.emplace_back(nebula::Row({1}));
      ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
      ASSERT_EQ(*resp.spaceName, "session_pool_test");
    });
  }
  for (auto& t : threads) {
    t.join();
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
