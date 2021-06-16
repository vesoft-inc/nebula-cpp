/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>

#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Init.h>
#include <nebula/client/Session.h>

#include "./ClientTest.h"

// Require a nebula server could access

#define kServerHost "graphd"

class ConfigTest : public ClientTest {};

TEST_F(ConfigTest, Timeout) {
    {
        // don't set
        nebula::ConnectionPool pool;
        nebula::Config c{};
        ASSERT_EQ(c.timeout_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_EQ(pool.size(), 10);
    }
    {
        // set to 0
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.timeout_ = 0;
        ASSERT_EQ(c.timeout_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_EQ(pool.size(), 10);
    }
    {
        // set to positive integer
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.timeout_ = 3;
        ASSERT_EQ(c.timeout_, 3);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_EQ(pool.size(), 10);
    }
}

TEST_F(ConfigTest, IdleTime) {
    {
        // don't set
        nebula::ConnectionPool pool;
        nebula::Config c{};
        ASSERT_EQ(c.idleTime_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_EQ(pool.size(), 10);
    }
    {
        // set to 0
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.idleTime_ = 0;
        ASSERT_EQ(c.idleTime_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_EQ(pool.size(), 10);
    }
    {
        // set to positive number
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.idleTime_ = 3;
        ASSERT_EQ(c.idleTime_, 3);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_EQ(pool.size(), 10);
    }
}

TEST_F(ClientTest, maxConnectionPoolSize) {
    {
        // don't set
        nebula::ConnectionPool pool;
        nebula::Config c{};
        ASSERT_EQ(c.maxConnectionPoolSize_, 10);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_LE(pool.size(), c.maxConnectionPoolSize_);
        EXPECT_GE(pool.size(), c.minConnectionPoolSize_);
    }
    {
        // set to positive number
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.maxConnectionPoolSize_ = 5;
        ASSERT_EQ(c.maxConnectionPoolSize_, 5);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_LE(pool.size(), c.maxConnectionPoolSize_);
        EXPECT_GE(pool.size(), c.minConnectionPoolSize_);
    }
    {
        // set to zero
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.maxConnectionPoolSize_ = 0;
        ASSERT_EQ(c.maxConnectionPoolSize_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_LE(pool.size(), c.maxConnectionPoolSize_);
        EXPECT_GE(pool.size(), c.minConnectionPoolSize_);
    }
}

TEST_F(ClientTest, minConnectionPoolSize) {
    {
        // don't set
        nebula::ConnectionPool pool;
        nebula::Config c{};
        ASSERT_EQ(c.minConnectionPoolSize_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_LE(pool.size(), c.maxConnectionPoolSize_);
        EXPECT_GE(pool.size(), c.minConnectionPoolSize_);
    }
    {
        // set to zero
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.minConnectionPoolSize_ = 0;
        ASSERT_EQ(c.minConnectionPoolSize_, 0);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_LE(pool.size(), c.maxConnectionPoolSize_);
        EXPECT_GE(pool.size(), c.minConnectionPoolSize_);
    }
    {
        // set to positive number
        nebula::ConnectionPool pool;
        nebula::Config c{};
        c.minConnectionPoolSize_ = 4;
        ASSERT_EQ(c.minConnectionPoolSize_, 4);
        pool.init({kServerHost ":9669"}, c);
        EXPECT_LE(pool.size(), c.maxConnectionPoolSize_);
        EXPECT_GE(pool.size(), c.minConnectionPoolSize_);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    nebula::init(&argc, &argv);
    google::SetStderrLogging(google::INFO);

    return RUN_ALL_TESTS();
}
