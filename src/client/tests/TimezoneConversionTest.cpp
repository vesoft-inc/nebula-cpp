/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Init.h>
#include <nebula/client/Session.h>

#include <atomic>
#include <chrono>
#include <thread>

#include "../../ClientTest.h"

// Require a nebula server could access

#define kServerHost "graphd"

class SessionTest : public ClientTest {};

TEST_F(SessionTest, Basic) {
  nebula::ConnectionPool pool;
  pool.init({kServerHost ":9669"}, nebula::Config{});
  auto session = pool.getSession("root", "nebula");
  ASSERT_TRUE(session.valid());
  {
    auto resp = session.execute(
        "YIELD datetime(\"2019-03-22T22:04:30\") as dt,"
        "date(\"2019-03-22\") as d, "
        "time(\"22:04:30\") as t");
    nebula::DataSet data({"dt", "d", "t"});
    data.emplace_back(nebula::Row({nebula::DateTime(2019, 3, 22, 22, 4, 30, 0),
                                   nebula::Date(2019, 3, 22),
                                   nebula::Time(22, 4, 30, 0)}));
    EXPECT_TRUE(verifyResultWithoutOrder(resp, data));

    // conversion
    session.toLocal(*resp.data);
    EXPECT_TRUE(verifyResultWithoutOrder(*resp.data, data));
  }
  {
    auto resp = session.execute(
        "YIELD datetime(\"2019-03-22T22:04:30\") as dt,"
        "date(\"2019-03-22\") as d, "
        "time(\"22:04:30\") as t");
    nebula::DataSet data({"dt", "d", "t"});
    data.emplace_back(nebula::Row({nebula::DateTime(2019, 3, 22, 22, 4, 30, 0),
                                   nebula::Date(2019, 3, 22),
                                   nebula::Time(22, 4, 30, 0)}));
    EXPECT_TRUE(verifyResultWithoutOrder(resp, data));

    // conversion
    session.toLocal(*resp.data, 30);
    nebula::DataSet expectLocal({"dt", "d", "t"});
    expectLocal.emplace_back(nebula::Row({nebula::DateTime(2019, 3, 22, 22, 5, 0, 0),
                                          nebula::Date(2019, 3, 22),
                                          nebula::Time(22, 5, 0, 0)}));
    EXPECT_TRUE(verifyResultWithoutOrder(*resp.data, expectLocal));
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
