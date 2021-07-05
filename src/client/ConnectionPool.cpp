/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <folly/String.h>
#include <atomic>
#include <mutex>
#include <thread>

#include "nebula/client/ConnectionPool.h"

namespace nebula {

ConnectionPool::~ConnectionPool() {
    close();
}

void ConnectionPool::init(const std::vector<std::string> &addresses, const Config &config) {
    for (const auto &addr : addresses) {
        std::vector<std::string> splits;
        folly::split(':', addr, splits, true);
        if (splits.size() != 2) {
            // ignore error
            continue;
        }
        address_.emplace_back(std::make_pair(splits[0], folly::to<int32_t>(splits[1])));
    }
    if (address_.empty()) {
        // no valid address
        return;
    }
    config_ = config;
    newConnection(0, config.maxConnectionPoolSize_);

    keepAlive_.store(true, std::memory_order_release);
    maintainer_ = std::thread(&ConnectionPool::keepAliveJob, this);
}

void ConnectionPool::close() {
    {
        std::lock_guard<std::mutex> l(lock_);
        for (auto &conn : conns_) {
            conn.close();
        }
    }
    keepAlive_.store(false, std::memory_order_release);
    if (maintainer_.joinable()) {
        maintainer_.join();
    }
}

Session ConnectionPool::getSession(const std::string &username,
                                   const std::string &password,
                                   bool retryConnect) {
    Connection conn = getConnection();
    auto resp = conn.authenticate(username, password);
    if (resp.errorCode != ErrorCode::SUCCEEDED || resp.sessionId == nullptr) {
        return Session();
    }
    return Session(*resp.sessionId,
                   std::move(conn),
                   this,
                   username,
                   password,
                   *resp.timeZoneName,
                   *resp.timeZoneOffsetSeconds,
                   retryConnect);
}

Connection ConnectionPool::getConnection() {
    std::lock_guard<std::mutex> l(lock_);
    // check connection
    for (auto c = conns_.begin(); c != conns_.end();) {
        if (!c->isOpen()) {
            c = conns_.erase(c);
            newConnection(nextCursor(), 1);
        } else {
            c++;
        }
    }
    if (conns_.empty()) {
        return Connection();
    }
    Connection conn = std::move(conns_.front());
    conns_.pop_front();
    return conn;
}

void ConnectionPool::giveBack(Connection &&conn) {
    std::lock_guard<std::mutex> l(lock_);
    conns_.emplace_back(std::move(conn));
}

void ConnectionPool::newConnection(std::size_t cursor, std::size_t count) {
    for (std::size_t connectionCount = 0, addrCursor = cursor, loopCount = 0;
         connectionCount < count;
         ++addrCursor, ++loopCount) {
        if (loopCount > count * address_.size()) {
            // Can't get so many connections, return to avoid dead loop
            return;
        }
        if (addrCursor >= address_.size()) {
            addrCursor = 0;
        }
        Connection conn;
        if (conn.open(address_[addrCursor].first, address_[addrCursor].second, config_.timeout_)) {
            ++connectionCount;
            conns_.emplace_back(std::move(conn));
        }
        // ignore error
    }
}

void ConnectionPool::keepAliveJob() {
    while (keepAlive_.load(std::memory_order_acquire)) {
        {
            std::lock_guard<std::mutex> l(lock_);
            std::size_t invalid = 0;
            for (auto c = conns_.begin(); c != conns_.end();) {
                if (!c->ping()) {
                    invalid++;
                    c = conns_.erase(c);
                } else {
                    c++;
                }
            }
            newConnection(nextCursor(), invalid);
        }

        using namespace std::chrono_literals;  // NOLINT
        std::this_thread::sleep_for(1s);
    }
}

}   // namespace nebula
