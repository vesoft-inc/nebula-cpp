/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include "nebula/client/Config.h"
#include "nebula/client/Connection.h"
#include "nebula/client/Session.h"

namespace nebula {

class ConnectionPool {
public:
    ~ConnectionPool();

    void init(const std::vector<std::string> &addresses, const Config &config);

    void close();

    Session getSession(const std::string &username,
                       const std::string &password,
                       bool retryConnect = true);

    Connection getConnection();

    void giveBack(Connection &&conn);

    std::size_t size() const {
        std::lock_guard<std::mutex> l(lock_);
        return conns_.size();
    }

private:
    // The count may can't perform if can't create enough valid connection
    void newConnection(std::size_t cursor, std::size_t count);

    std::size_t nextCursor() {
        return cursor_ >= address_.size() ? cursor_ = 0 : cursor_++;
    }

    std::size_t                                  cursor_{0};
    // host, port
    std::vector<std::pair<std::string, int32_t>> address_;

    mutable std::mutex lock_;
    std::list<Connection> conns_;
};

}   // namespace nebula
