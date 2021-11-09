/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "nebula/client/Connection.h"

#include <folly/SocketAddress.h>
#include <folly/io/async/AsyncSSLSocket.h>
#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/ScopedEventBaseThread.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>

#include <memory>
#include <stdexcept>

#include "./SSLConfig.h"
#include "interface/gen-cpp2/GraphServiceAsyncClient.h"

namespace nebula {

class NebulaConnectionErrMessageCallback : public folly::AsyncSocket::ErrMessageCallback {
 public:
  /**
   * errMessage() will be invoked when kernel puts a message to
   * the error queue associated with the socket.
   *
   * @param cmsg      Reference to cmsghdr structure describing
   *                  a message read from error queue associated
   *                  with the socket.
   */
  void errMessage(const cmsghdr &) noexcept override {
    DLOG(ERROR) << "Connection error.";
  }

  /**
   * errMessageError() will be invoked if an error occurs reading a message
   * from the socket error stream.
   *
   * @param ex        An exception describing the error that occurred.
   */
  void errMessageError(const folly::AsyncSocketException &ex) noexcept override {
    DLOG(ERROR) << "Connection error: " << ex.what();
  }

  static auto &instance() { return cb_; }

 private:
  static NebulaConnectionErrMessageCallback cb_;
};

NebulaConnectionErrMessageCallback NebulaConnectionErrMessageCallback::cb_;

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

  return *this;
}

bool Connection::open(const std::string &address,
                      int32_t port,
                      uint32_t timeout,
                      bool enableSSL,
                      const std::string &CAPath) {
  if (address.empty()) {
    return false;
  }
  bool complete{false};
  clientLoopThread_->getEventBase()->runInEventBaseThreadAndWait(
      [this, &complete, &address, port, timeout, enableSSL, &CAPath]() {
        try {
          std::shared_ptr<folly::AsyncSocket> socket;
          auto socketAddr = folly::SocketAddress(address, port, true);
          if (enableSSL) {
            socket = folly::AsyncSSLSocket::newSocket(nebula::createSSLContext(CAPath),
                                                      clientLoopThread_->getEventBase());
            socket->connect(nullptr, std::move(socketAddr), timeout);
          } else {
            socket = folly::AsyncSocket::newSocket(
                clientLoopThread_->getEventBase(), std::move(socketAddr), timeout);
          }
          socket->setErrMessageCB(&NebulaConnectionErrMessageCallback::instance());
          auto channel = apache::thrift::HeaderClientChannel::newChannel(socket);
          channel->setTimeout(timeout);
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
    return AuthResponse{
        ErrorCode::E_DISCONNECTED, nullptr, std::make_unique<std::string>("Not open connection.")};
  }

  AuthResponse resp;
  try {
    resp = client_->future_authenticate(user, password).get();
  } catch (const std::exception &ex) {
    resp =
        AuthResponse{ErrorCode::E_RPC_FAILURE, nullptr, std::make_unique<std::string>(ex.what())};
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
  } catch (const std::exception &ex) {
    resp = ExecutionResponse{
        ErrorCode::E_RPC_FAILURE, 0, nullptr, nullptr, std::make_unique<std::string>(ex.what())};
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
  client_->future_execute(sessionId, stmt).thenValue([cb = std::move(cb)](auto &&resp) {
    cb(std::move(resp));
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

bool Connection::isOpen() { return ping(); }

void Connection::close() {
  if (client_ != nullptr) {
    clientLoopThread_->getEventBase()->runInEventBaseThreadAndWait([this]() { delete client_; });
    client_ = nullptr;
  }
}

bool Connection::ping() {
  auto resp = execute(0 /*Only check connection*/, "YIELD 1");
  if (resp.errorCode == ErrorCode::E_RPC_FAILURE || resp.errorCode == ErrorCode::E_DISCONNECTED) {
    return false;
  }
  return true;
}

void Connection::signout(int64_t sessionId) {
  if (client_ != nullptr) {
    client_->future_signout(sessionId).wait();
  }
}

}  // namespace nebula
