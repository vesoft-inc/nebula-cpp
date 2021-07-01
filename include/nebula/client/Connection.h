/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>

#include "common/graph/Response.h"

namespace folly {
class ScopedEventBaseThread;
}

namespace nebula {

// Wrap the thrift client.
namespace graph {
namespace cpp2 {
class GraphServiceAsyncClient;
}
}

class Connection {
public:
    using ExecuteCallback = std::function<void(ExecutionResponse &&)>;
    using ExecuteJsonCallback = std::function<void(std::string &&)>;

    Connection();
    // disable copy
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &c) = delete;

    Connection(Connection &&c) noexcept {
        client_ = c.client_;
        c.client_ = nullptr;

        clientLoopThread_ = c.clientLoopThread_;
        c.clientLoopThread_ = nullptr;
    }

    Connection &operator=(Connection &&c);

    ~Connection();

    bool open(const std::string &address, int32_t port, uint32_t timeout);

    AuthResponse authenticate(const std::string &user, const std::string &password);

    ExecutionResponse execute(int64_t sessionId, const std::string &stmt);

    void asyncExecute(int64_t sessionId, const std::string &stmt, ExecuteCallback cb);

    std::string executeJson(int64_t sessionId, const std::string &stmt);

    void asyncExecuteJson(int64_t sessionId, const std::string &stmt, ExecuteJsonCallback cb);

    bool isOpen();

    void close();

    bool ping();

    void signout(int64_t sessionId);

private:
    graph::cpp2::GraphServiceAsyncClient *client_{nullptr};
    folly::ScopedEventBaseThread         *clientLoopThread_{nullptr};
};

}   // namespace nebula
