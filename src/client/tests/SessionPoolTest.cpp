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
    nebula::Config cfg{0, 0, 1, 0, false, false, false, "", "", "", ""};
    pool.init({kServerHost ":9669"}, cfg);
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());

    auto resp = session.execute(
        "CREATE SPACE IF NOT EXISTS session_pool_test(vid_type = FIXED_STRING(16));"
        "CREATE SPACE IF NOT EXISTS session_pool_test2(vid_type = FIXED_STRING(16));");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    resp = session.execute("CREATE USER test_user WITH PASSWORD 'test_user';");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;
    ::sleep(20);  // wait schema sync
  }

  void TearDown() {
    nebula::ConnectionPool pool;
    nebula::Config cfg{0, 0, 1, 0, false, false, false, "", "", "", ""};
    pool.init({kServerHost ":9669"}, cfg);
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());

    auto resp = session.execute("DROP SPACE session_pool_test;DROP SPACE session_pool_test2;");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    resp = session.execute("DROP USER test_user;");
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

// case 1
TEST_F(SessionPoolTest, Exception) {
  // space don't exists
  {
    nebula::SessionPoolConfig config;
    config.username_ = "root";
    config.password_ = "nebula";
    config.addrs_ = {kServerHost ":9669"};
    config.spaceName_ = "not_exists_space";
    config.maxSize_ = 2;
    nebula::SessionPool pool(config);
    ASSERT_FALSE(pool.init());
  }

  // user don't exists
  {
    nebula::SessionPoolConfig config;
    config.username_ = "not_exists_user";
    config.password_ = "nebula";
    config.addrs_ = {kServerHost ":9669"};
    config.spaceName_ = "session_pool_test";
    config.maxSize_ = 2;
    nebula::SessionPool pool(config);
    ASSERT_FALSE(pool.init());
  }

  // user password error
  {
    nebula::SessionPoolConfig config;
    config.username_ = "test_user";
    config.password_ = "not_exists_password";
    config.addrs_ = {kServerHost ":9669"};
    config.spaceName_ = "session_pool_test";
    config.maxSize_ = 2;
    nebula::SessionPool pool(config);
    ASSERT_FALSE(pool.init());
  }
}

// case 2
TEST_F(SessionPoolTest, Normal) {
  // over connection limit
  {
    nebula::SessionPoolConfig config;
    config.username_ = "root";
    config.password_ = "nebula";
    config.addrs_ = {kServerHost ":9669"};
    config.spaceName_ = "session_pool_test";
    config.maxSize_ = 2;
    nebula::SessionPool pool(config);
    ASSERT_TRUE(pool.init());
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < 5; ++i) {
      threads.emplace_back([&pool]() {
        auto resp = pool.execute("YIELD 1");
        nebula::DataSet expected({"1"});
        expected.emplace_back(nebula::Row({1}));
        if (resp.errorCode == nebula::ErrorCode::SUCCEEDED) {
          ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
          ASSERT_EQ(*resp.spaceName, "session_pool_test");
        } else {
          ASSERT_EQ(*resp.errorMsg, "No idle session.");
        }
      });
    }
    for (auto& t : threads) {
      t.join();
    }
  }
}

// case 3
TEST_F(SessionPoolTest, SwitchSpace) {
  nebula::SessionPoolConfig config;
  config.username_ = "root";
  config.password_ = "nebula";
  config.addrs_ = {kServerHost ":9669"};
  config.spaceName_ = "session_pool_test";
  config.maxSize_ = 1;
  nebula::SessionPool pool(config);
  pool.init();
  // switch space and auto switch back
  {
    auto resp = pool.execute("USE session_pool_test2;");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    resp = pool.execute("YIELD 1");
    nebula::DataSet expected({"1"});
    expected.emplace_back(nebula::Row({1}));
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");

    // return json
    auto json = pool.executeJson("USE session_pool_test2");
    auto obj = folly::parseJson(json);
    ASSERT_EQ(obj["errors"][0]["code"].asInt(), 0) << obj["errors"][0]["message"].asString();

    resp = pool.execute("YIELD 1");
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");
  }

  // switch to nonexistent space and auto switch back
  {
    auto resp = pool.execute("USE nonexistent_space; YIELD 1");
    ASSERT_NE(resp.errorCode, nebula::ErrorCode::SUCCEEDED);

    resp = pool.execute("YIELD 1");
    nebula::DataSet expected({"1"});
    expected.emplace_back(nebula::Row({1}));
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");

    // return json
    auto json = pool.executeJson("USE nonexistent_space; YIELD 1");
    auto obj = folly::parseJson(json);
    ASSERT_NE(obj["errors"][0]["code"].asInt(), 0);

    resp = pool.execute("YIELD 1");
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");
  }

  // switch to current space and auto switch back
  {
    auto resp = pool.execute("USE session_pool_test");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    resp = pool.execute("YIELD 1");
    nebula::DataSet expected({"1"});
    expected.emplace_back(nebula::Row({1}));
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");

    // return json
    auto json = pool.executeJson("USE session_pool_test");
    auto obj = folly::parseJson(json);
    ASSERT_EQ(obj["errors"][0]["code"].asInt(), 0) << obj["errors"][0]["message"].asString();

    resp = pool.execute("YIELD 1");
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");
  }

  // switch to two spaces and auto switch back
  {
    auto resp = pool.execute("USE session_pool_test; USE session_pool_test2");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    resp = pool.execute("YIELD 1");
    nebula::DataSet expected({"1"});
    expected.emplace_back(nebula::Row({1}));
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");

    // return json
    auto json = pool.executeJson("USE session_pool_test; USE session_pool_test2");
    auto obj = folly::parseJson(json);
    ASSERT_EQ(obj["errors"][0]["code"].asInt(), 0) << obj["errors"][0]["message"].asString();

    resp = pool.execute("YIELD 1");
    ASSERT_TRUE(verifyResultWithoutOrder(resp, expected));
    ASSERT_EQ(*resp.spaceName, "session_pool_test");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
