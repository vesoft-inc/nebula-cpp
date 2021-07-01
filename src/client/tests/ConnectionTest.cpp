/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

#include <nebula/client/Connection.h>
#include <nebula/client/Init.h>

#include "./ClientTest.h"

// Require a nebula server could access

static constexpr char kServerHost[] = "graphd";

class ConnectionTest : public ClientTest {
protected:
    static void runOnce(nebula::Connection &c) {
        // ping
        EXPECT_FALSE(c.ping());

        // execute
        auto resp = c.execute(-1, "SHOW SPACES");
        ASSERT_TRUE(resp.errorCode == nebula::ErrorCode::E_DISCONNECTED ||
                    resp.errorCode == nebula::ErrorCode::E_RPC_FAILURE);
        EXPECT_EQ(resp.data, nullptr);

        // async execute
        c.asyncExecute(-1, "SHOW SPACES", [](auto &&cbResp) {
            ASSERT_TRUE(cbResp.errorCode == nebula::ErrorCode::E_DISCONNECTED ||
                        cbResp.errorCode == nebula::ErrorCode::E_RPC_FAILURE);
            EXPECT_EQ(cbResp.data, nullptr);
        });

        // open
        ASSERT_TRUE(c.open(kServerHost, 9669, 0));

        // ping
        EXPECT_TRUE(c.ping());

        // auth
        auto authResp = c.authenticate("root", "nebula");
        ASSERT_EQ(authResp.errorCode, nebula::ErrorCode::SUCCEEDED);

        // execute
        resp = c.execute(*authResp.sessionId, "SHOW SPACES");
        ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
        nebula::DataSet expected({"Name"});
        EXPECT_TRUE(verifyResultWithoutOrder(*resp.data, expected));

        // explain
        resp = c.execute(*authResp.sessionId, "EXPLAIN SHOW HOSTS");
        ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
        EXPECT_NE(resp.planDesc, nullptr);
        // TODO(shylock) check the plan

        // async execute
        folly::Baton<> b;
        c.asyncExecute(*authResp.sessionId, "SHOW SPACES", [&b](auto &&cbResp) {
            ASSERT_EQ(cbResp.errorCode, nebula::ErrorCode::SUCCEEDED)
                << static_cast<int>(cbResp.errorCode);
            nebula::DataSet cbExpected({"Name"});
            EXPECT_TRUE(verifyResultWithoutOrder(*cbResp.data, cbExpected));
            b.post();
        });
        b.wait();

        // signout
        c.signout(*authResp.sessionId);

        // ping
        EXPECT_TRUE(c.ping());

        // check signout
        resp = c.execute(*authResp.sessionId, "SHOW SPACES");
        ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_SESSION_INVALID);

        // async execute
        folly::Baton<> b1;
        c.asyncExecute(*authResp.sessionId, "SHOW SPACES", [&b1](auto &&cbResp) {
            ASSERT_EQ(cbResp.errorCode, nebula::ErrorCode::E_SESSION_INVALID);
            b1.post();
        });
        b1.wait();

        // close
        c.close();

        // ping
        EXPECT_FALSE(c.ping());

        // execute
        resp = c.execute(*authResp.sessionId, "SHOW SPACES");
        ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_DISCONNECTED);

        // async execute
        folly::Baton<> b2;
        c.asyncExecute(*authResp.sessionId, "SHOW SPACES", [&b2](auto &&cbResp) {
            ASSERT_EQ(cbResp.errorCode, nebula::ErrorCode::E_DISCONNECTED);
            b2.post();
        });
        b2.wait();

        // isOpen
        EXPECT_FALSE(c.isOpen());
    }
};

TEST_F(ConnectionTest, Basic) {
    nebula::Connection c;
    LOG(INFO) << "Testing once.";
    runOnce(c);
    LOG(INFO) << "Testing reopen.";
    runOnce(c);
}

TEST_F(ConnectionTest, Timeout) {
    nebula::Connection c;

    ASSERT_TRUE(c.open(kServerHost, 9669, 5));

    // auth
    auto authResp = c.authenticate("root", "nebula");
    ASSERT_EQ(authResp.errorCode, nebula::ErrorCode::SUCCEEDED);

    // execute
    auto resp = c.execute(*authResp.sessionId,
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;"
                          "show spaces;show spaces;show spaces;show spaces;");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_RPC_FAILURE);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    nebula::init(&argc, &argv);
    google::SetStderrLogging(google::INFO);

    return RUN_ALL_TESTS();
}
