/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <memory>

#include <folly/SocketAddress.h>
#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/ScopedEventBaseThread.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>

#include "common/interface/gen-cpp2/GraphServiceAsyncClient.h"
#include "nebula/client/Connection.h"

namespace nebula {

Connection::Connection()
    : client_{nullptr}, clientLoopThread_(new folly::ScopedEventBaseThread()) {}

Connection::~Connection() {
    close();
    delete clientLoopThread_;
}

Connection &Connection::operator=(Connection &&c) {
    close();
    client_ = c.client_;
    c.client_ = nullptr;

    delete clientLoopThread_;
    clientLoopThread_ = c.clientLoopThread_;
    c.clientLoopThread_ = nullptr;

    address_ = std::move(c.address_);
    port_ = c.port_;
    c.port_ = 0;
    timeout_ = c.timeout_;
    c.timeout_ = 0;

    return *this;
}

bool Connection::open(const std::string &address, int32_t port, uint32_t timeout) {
    if (address.empty()) {
        return false;
    }
    address_ = address;
    port_ = port;
    timeout_ = timeout;
    return open();
}

bool Connection::open() {
    bool complete{false};
    clientLoopThread_->getEventBase()->runInEventBaseThreadAndWait([this, &complete]() {
        try {
            auto socketAddr = folly::SocketAddress(address_, port_, true);
            auto socket = folly::AsyncSocket::UniquePtr(new folly::AsyncSocket(
                clientLoopThread_->getEventBase(), std::move(socketAddr), timeout_));
            auto channel = apache::thrift::HeaderClientChannel::newChannel(std::move(socket));
            channel->setTimeout(timeout_);
            client_ = new graph::cpp2::GraphServiceAsyncClient(std::move(channel));
            complete = true;
        } catch (const std::exception &) {
            complete = false;
        }
    });
    return complete;
}

AuthResponse Connection::authenticate(const std::string &user, const std::string &password) {
    if (client_ == nullptr) {
        return AuthResponse{ErrorCode::E_DISCONNECTED,
                            nullptr,
                            std::make_unique<std::string>("Not open connection.")};
    }

    AuthResponse resp;
    try {
        resp = client_->future_authenticate(user, password).get();
    } catch (const std::exception &ex) {
        resp = AuthResponse{
            ErrorCode::E_RPC_FAILURE, nullptr, std::make_unique<std::string>(ex.what())};
    }
    return resp;
}

ExecutionResponse Connection::execute(int64_t sessionId, const std::string &stmt) {
    if (client_ == nullptr) {
        return ExecutionResponse{ErrorCode::E_DISCONNECTED,
                                 0,
                                 nullptr,
                                 nullptr,
                                 std::make_unique<std::string>("Not open connection.")};
    }

    ExecutionResponse resp;
    try {
        resp = client_->future_execute(sessionId, stmt).get();
    } catch (const ::apache::thrift::transport::TTransportException &ex) {
        if (ex.getType() ==
            ::apache::thrift::transport::TTransportException::TTransportExceptionType::TIMED_OUT) {
            resp = ExecutionResponse{ErrorCode::E_RPC_TIMEOUT,
                                     0,
                                     nullptr,
                                     nullptr,
                                     std::make_unique<std::string>(ex.what())};
        } else {
            resp = ExecutionResponse{ErrorCode::E_RPC_FAILURE,
                                     0,
                                     nullptr,
                                     nullptr,
                                     std::make_unique<std::string>(ex.what())};
        }
    } catch (const std::exception &ex) {
        resp = ExecutionResponse{ErrorCode::E_RPC_FAILURE,
                                 0,
                                 nullptr,
                                 nullptr,
                                 std::make_unique<std::string>(ex.what())};
    }

    return resp;
}

void Connection::asyncExecute(int64_t sessionId, const std::string &stmt, ExecuteCallback cb) {
    if (client_ == nullptr) {
        cb(ExecutionResponse{ErrorCode::E_DISCONNECTED,
                             0,
                             nullptr,
                             nullptr,
                             std::make_unique<std::string>("Not open connection.")});
        return;
    }
    client_->future_execute(sessionId, stmt).thenTry([cb = std::move(cb)](auto &&t) {
        if (t.hasException()) {
            auto ex =
                t.template tryGetExceptionObject<apache::thrift::transport::TTransportException>();
            if (ex->getType() == ::apache::thrift::transport::TTransportException::
                                     TTransportExceptionType::TIMED_OUT) {
                cb(ExecutionResponse{ErrorCode::E_RPC_TIMEOUT,
                                     0,
                                     nullptr,
                                     nullptr,
                                     std::make_unique<std::string>(ex->what())});
            } else {
                cb(ExecutionResponse{ErrorCode::E_RPC_FAILURE,
                                     0,
                                     nullptr,
                                     nullptr,
                                     std::make_unique<std::string>(ex->what())});
            }
        } else {
            cb(std::move(t).value());
        }
    });
}

std::string Connection::executeJson(int64_t sessionId, const std::string &stmt) {
    if (client_ == nullptr) {
        // TODO handle error
        return "";
    }

    std::string json;
    try {
        json = client_->future_executeJson(sessionId, stmt).get();
    } catch (const std::exception &ex) {
        // TODO handle error
        json = "";
    }

    return json;
}

void Connection::asyncExecuteJson(int64_t sessionId,
                                  const std::string &stmt,
                                  ExecuteJsonCallback cb) {
    if (client_ == nullptr) {
        // TODO handle error
        cb("");
        return;
    }
    client_->future_executeJson(sessionId, stmt).thenValue(std::move(cb));
}

bool Connection::isOpen() {
    return ping();
}

void Connection::close() {
    if (client_ != nullptr) {
        clientLoopThread_->getEventBase()->runInEventBaseThreadAndWait(
            [this]() { delete client_; });
        client_ = nullptr;
    }
}

bool Connection::ping() {
    auto resp = execute(0 /*Only check connection*/, "YIELD 1");
    if (resp.errorCode == ErrorCode::E_RPC_FAILURE || resp.errorCode == ErrorCode::E_DISCONNECTED ||
        resp.errorCode == ErrorCode::E_RPC_TIMEOUT) {
        return false;
    }
    return true;
}

void Connection::signout(int64_t sessionId) {
    if (client_ != nullptr) {
        client_->future_signout(sessionId).wait();
    }
}

}   // namespace nebula
