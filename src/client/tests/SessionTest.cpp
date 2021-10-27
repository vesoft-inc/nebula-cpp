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

#include <nebula/client/Config.h>
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
        auto result = session.execute("YIELD 1");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
        nebula::DataSet expected({"1"});
        expected.emplace_back(nebula::List({1}));
        EXPECT_TRUE(verifyResultWithoutOrder(*result.data, expected));

        // explain
        result = session.execute("EXPLAIN SHOW HOSTS");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
        EXPECT_NE(result.planDesc, nullptr);
        // TODO(shylock) check the plan

        // async execute
        folly::Baton<> b;
        session.asyncExecute("YIELD 1", [&b](auto&& cbResult) {
            ASSERT_EQ(cbResult.errorCode, nebula::ErrorCode::SUCCEEDED);
            nebula::DataSet cbExpected({"1"});
            cbExpected.emplace_back(nebula::List({1}));
            EXPECT_TRUE(verifyResultWithoutOrder(*cbResult.data, cbExpected));
            b.post();
        });
        b.wait();

        // retry connection
        ASSERT_EQ(session.retryConnect(), nebula::ErrorCode::SUCCEEDED);

        // execute
        result = session.execute("YIELD 1");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::SUCCEEDED);
        EXPECT_TRUE(verifyResultWithoutOrder(*result.data, expected));

        // release
        session.release();

        ASSERT_FALSE(session.valid());

        // ping
        EXPECT_FALSE(session.ping());

        // check release
        result = session.execute("YIELD 1");
        ASSERT_EQ(result.errorCode, nebula::ErrorCode::E_DISCONNECTED);

        // async execute
        folly::Baton<> b2;
        session.asyncExecute("YIELD 1", [&b2](auto&& cbResult) {
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
        threads.emplace_back([&pool]() {
            using namespace std::chrono_literals;   // NOLINT
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

TEST_F(SessionTest, Timeout) {
    nebula::ConnectionPool pool;
    nebula::Config c{10, 0, 10, 0};
    pool.init({kServerHost ":9669"}, c);
    auto session = pool.getSession("root", "nebula");
    ASSERT_TRUE(session.valid());

    auto resp =
        session.execute("CREATE SPACE IF NOT EXISTS session_test(vid_type = FIXED_STRING(16));use "
                        "session_test;CREATE EDGE IF NOT EXISTS like();");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    ::sleep(30);

    resp = session.execute("INSERT EDGE like() VALUES 'Tim Duncan'->'Tony Parker':(), 'Tony "
                           "Parker'->'Tim Duncan':();");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

    // execute
    resp = session.execute(
        "use session_test;GO 100000 STEPS FROM 'Tim Duncan' OVER like YIELD like._dst;");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_RPC_FAILURE) << *resp.errorMsg;

    resp = session.execute(
        "SHOW QUERIES "
        "| YIELD $-.SessionID AS sid, $-.ExecutionPlanID AS eid, $-.DurationInUSec AS dur "
        "WHERE $-.DurationInUSec > 1000000 AND $-.`Query` CONTAINS 'GO' "
        "| ORDER BY $-.dur "
        "| KILL QUERY(session=$-.sid, plan=$-.eid)");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);

    resp = session.execute("DROP SPACE IF EXISTS session_test");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    nebula::init(&argc, &argv);
    google::SetStderrLogging(google::INFO);

    return RUN_ALL_TESTS();
}
