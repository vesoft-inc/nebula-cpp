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

class ConnectionTest : public ClientTest {
 protected:
  static void runOnce(nebula::Connection &c) {
    // ping
    EXPECT_FALSE(c.ping());

    // execute
    auto resp = c.execute(-1, "YIELD 1");
    ASSERT_TRUE(resp.errorCode == nebula::ErrorCode::E_DISCONNECTED ||
                resp.errorCode == nebula::ErrorCode::E_RPC_FAILURE);
    EXPECT_EQ(resp.data, nullptr);

    // async execute
    c.asyncExecute(-1, "YIELD 1", [](auto &&cbResp) {
      ASSERT_TRUE(cbResp.errorCode == nebula::ErrorCode::E_DISCONNECTED ||
                  cbResp.errorCode == nebula::ErrorCode::E_RPC_FAILURE);
      EXPECT_EQ(cbResp.data, nullptr);
    });

    // open
    ASSERT_TRUE(c.open(kServerHost, 9669, 0, false, ""));

    // ping
    EXPECT_TRUE(c.ping());

    // auth
    auto authResp = c.authenticate("root", "nebula");
    ASSERT_EQ(authResp.errorCode, nebula::ErrorCode::SUCCEEDED) << *authResp.errorMsg;

    // execute
    resp = c.execute(*authResp.sessionId, "YIELD 1");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
    nebula::DataSet expected({"1"});
    expected.emplace_back(nebula::List({1}));
    EXPECT_TRUE(verifyResultWithoutOrder(*resp.data, expected));

    // explain
    resp = c.execute(*authResp.sessionId, "EXPLAIN SHOW HOSTS");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
    EXPECT_NE(resp.planDesc, nullptr);
    // TODO(shylock) check the plan

    // async execute
    folly::Baton<> b;
    c.asyncExecute(*authResp.sessionId, "YIELD 1", [&b](auto &&cbResp) {
      ASSERT_EQ(cbResp.errorCode, nebula::ErrorCode::SUCCEEDED)
          << static_cast<int>(cbResp.errorCode);
      nebula::DataSet cbExpected({"1"});
      cbExpected.emplace_back(nebula::List({1}));
      EXPECT_TRUE(verifyResultWithoutOrder(*cbResp.data, cbExpected));
      b.post();
    });
    b.wait();

    // signout
    c.signout(*authResp.sessionId);

    // TODO(shylock) the signout don't complete in server side even if request returned
    // Trick sleep to wait it
    sleep(1);

    // ping
    EXPECT_TRUE(c.ping());

    // check signout
    resp = c.execute(*authResp.sessionId, "YIELD 1");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_SESSION_INVALID);

    // async execute
    folly::Baton<> b1;
    c.asyncExecute(*authResp.sessionId, "YIELD 1", [&b1](auto &&cbResp) {
      ASSERT_EQ(cbResp.errorCode, nebula::ErrorCode::E_SESSION_INVALID);
      b1.post();
    });
    b1.wait();

    // close
    c.close();

    // ping
    EXPECT_FALSE(c.ping());

    // execute
    resp = c.execute(*authResp.sessionId, "YIELD 1");
    ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_DISCONNECTED);

    // async execute
    folly::Baton<> b2;
    c.asyncExecute(*authResp.sessionId, "YIELD 1", [&b2](auto &&cbResp) {
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

  ASSERT_TRUE(c.open(kServerHost, 9669, 100, false, ""));

  // auth
  auto authResp = c.authenticate("root", "nebula");
  ASSERT_EQ(authResp.errorCode, nebula::ErrorCode::SUCCEEDED);

  auto resp = c.execute(*authResp.sessionId,
                        "CREATE SPACE IF NOT EXISTS conn_test(vid_type = FIXED_STRING(16));use "
                        "conn_test;CREATE EDGE IF NOT EXISTS like();");
  ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

  ::sleep(30);

  resp = c.execute(*authResp.sessionId,
                   "INSERT EDGE like() VALUES 'Tim Duncan'->'Tony Parker':(), 'Tony "
                   "Parker'->'Tim Duncan':();");
  ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;

  // execute
  resp = c.execute(*authResp.sessionId,
                   "use conn_test;GO 100000 STEPS FROM 'Tim Duncan' OVER like YIELD like._dst;");
  ASSERT_EQ(resp.errorCode, nebula::ErrorCode::E_RPC_FAILURE) << *resp.errorMsg;

  resp =
      c.execute(*authResp.sessionId,
                "SHOW QUERIES "
                "| YIELD $-.SessionID AS sid, $-.ExecutionPlanID AS eid, $-.DurationInUSec AS dur "
                "WHERE $-.DurationInUSec > 1000000 AND $-.`Query` CONTAINS 'GO' "
                "| ORDER BY $-.dur "
                "| KILL QUERY(session=$-.sid, plan=$-.eid)");
  ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);

  resp = c.execute(*authResp.sessionId, "DROP SPACE IF EXISTS conn_test");
  ASSERT_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED);
}

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

TEST_F(ConnectionTest, JsonResult) {
  nebula::Connection c;

  ASSERT_TRUE(c.open(kServerHost, 9669, 10, false, ""));

  // auth
  auto authResp = c.authenticate("root", "nebula");
  ASSERT_EQ(authResp.errorCode, nebula::ErrorCode::SUCCEEDED);

  auto resp = c.executeJson(*authResp.sessionId, "YIELD 1");
  folly::parseJson(resp);

  folly::Baton<> b1;
  c.asyncExecuteJson(*authResp.sessionId, "YIELD 1", [&b1](std::string &&asyncResp) {
    folly::parseJson(asyncResp);
    b1.post();
  });
  b1.wait();
}

TEST_F(ConnectionTest, InvalidPort) {
  nebula::Connection c;

  ASSERT_FALSE(c.open(kServerHost, 2333, 10, false, ""));
}

TEST_F(ConnectionTest, InvalidHost) {
  nebula::Connection c;

  ASSERT_FALSE(c.open("Invalid Host", 9669, 10, false, ""));
}

TEST_F(ConnectionTest, ConstructDestruct) {
  nebula::Connection c;

  ASSERT_TRUE(c.open(kServerHost, 9669, 10, false, ""));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
