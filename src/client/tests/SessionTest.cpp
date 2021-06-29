/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <atomic>
#include <chrono>
#include <thread>

#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>

#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Init.h>
#include <nebula/client/Session.h>

#include "./ClientTest.h"

// Require a nebula server could access

#define kServerHost "graphd"

class SessionTest : public ClientTest {
protected:
    static void runOnce(nebula::ConnectionPool& pool) {
        auto session = pool.getSession("root", "nebula");
        ASSERT_TRUE(session.valid());

        // ping
        EXPECT_TRUE(session.ping());

        // execute
        auto result = session.execute("SHOW SPACES");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
        nebula::DataSet expected({"Name"});
        EXPECT_TRUE(verifyResultWithoutOrder(*result.data, expected));

        // explain
        result = session.execute("EXPLAIN SHOW HOSTS");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
        EXPECT_NE(result.planDesc, nullptr);
        // TODO(shylock) check the plan

        // async execute
        folly::Baton<> b;
        session.asyncExecute("SHOW SPACES", [&b](auto&& cbResult) {
            ASSERT_EQ(cbResult.errorCode, nebula::ErrorCode::SUCCEEDED);
            nebula::DataSet cbExpected({"Name"});
            EXPECT_TRUE(verifyResultWithoutOrder(*cbResult.data, cbExpected));
            b.post();
        });
        b.wait();

        // retry connection
        ASSERT_EQ(session.retryConnect(), nebula::ErrorCode::SUCCEEDED);

        // execute
        result = session.execute("SHOW SPACES");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
        EXPECT_TRUE(verifyResultWithoutOrder(*result.data, expected));

        // release
        session.release();

        ASSERT_FALSE(session.valid());

        // ping
        EXPECT_FALSE(session.ping());

        // check release
        result = session.execute("SHOW SPACES");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::E_DISCONNECTED);

        // async execute
        folly::Baton<> b2;
        session.asyncExecute("SHOW SPACES", [&b2](auto&& cbResult) {
            ASSERT_EQ(cbResult.errorCode, nebula::ErrorCode::E_DISCONNECTED);
            b2.post();
        });
        b2.wait();

        // ping
        EXPECT_FALSE(session.ping());
    }
};

TEST_F(SessionTest, Basic) {
    nebula::ConnectionPool pool;
  pool.init({kServerHost ":9669"}, nebula::Config{});
    LOG(INFO) << "Testing once.";
    runOnce(pool);

    LOG(INFO) << "Testing reopen.";
    runOnce(pool);
}

TEST_F(SessionTest, OverUse) {
    nebula::ConnectionPool pool;
    nebula::Config c;
    pool.init({kServerHost ":9669"}, c);
    std::vector<nebula::Session> sessions;
    for (std::size_t i = 0; i < c.maxConnectionPoolSize_; ++i) {
        sessions.emplace_back(pool.getSession("root", "nebula"));
    }
    auto session = pool.getSession("root", "nebula");
    EXPECT_FALSE(session.valid());
}

TEST_F(SessionTest, MTSafe) {
    nebula::ConnectionPool pool;
    nebula::Config c;
    pool.init({kServerHost ":9669"}, c);
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < c.maxConnectionPoolSize_; ++i) {
        threads.emplace_back([&pool, i]() {
            using namespace std::chrono_literals;  // NOLINT
            std::this_thread::sleep_for(1s);

            auto session = pool.getSession("root", "nebula");
            EXPECT_TRUE(session.valid());

            session.release();
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    EXPECT_EQ(pool.size(), c.maxConnectionPoolSize_);
}

TEST_F(SessionTest, InvalidAddress) {
    nebula::ConnectionPool pool;
    nebula::Config c;
    pool.init({"xxxx"}, c);
    EXPECT_EQ(pool.size(), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    nebula::init(&argc, &argv);
    google::SetStderrLogging(google::INFO);

    return RUN_ALL_TESTS();
}
