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

#include "../SSLConfig.h"
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

  static auto &instance() {
    return cb_;
  }

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
  std::shared_ptr<folly::AsyncSocket> socket;
  folly::SocketAddress socketAddr;
  try {
    socketAddr = folly::SocketAddress(address, port, true);
  } catch (const std::exception &e) {
    DLOG(ERROR) << "Invalid address: " << address << ":" << port << ": " << e.what();
    return false;
  }
  clientLoopThread_->getEventBase()->runImmediatelyOrRunInEventBaseThreadAndWait(
      [this, &complete, &socket, timeout, &socketAddr, enableSSL, &CAPath]() {
        try {
          if (enableSSL) {
            socket = folly::AsyncSSLSocket::newSocket(nebula::createSSLContext(CAPath),
                                                      clientLoopThread_->getEventBase());
            socket->connect(nullptr, std::move(socketAddr), timeout);
          } else {
            socket = folly::AsyncSocket::newSocket(
                clientLoopThread_->getEventBase(), std::move(socketAddr), timeout);
          }
          complete = true;
        } catch (const std::exception &e) {
          DLOG(ERROR) << "Connect failed: " << e.what();
          complete = false;
        }
      });
  if (!complete) {
    return false;
  }
  if (!socket->good()) {
    return false;
  }
  // TODO workaround for issue #72
  // socket->setErrMessageCB(&NebulaConnectionErrMessageCallback::instance());
  auto channel = apache::thrift::HeaderClientChannel::newChannel(socket);
  channel->setTimeout(timeout);
  client_ = new graph::cpp2::GraphServiceAsyncClient(std::move(channel));
  auto resp = verifyClientVersion(VerifyClientVersionReq{});
  if (resp.errorCode != ErrorCode::SUCCEEDED) {
    DLOG(ERROR) << "Failed to verify client version: " << *resp.errorMsg;
    return false;
  }
  return true;
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
  return executeWithParameter(sessionId, stmt, {});
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

ExecutionResponse Connection::executeWithParameter(
    int64_t sessionId,
    const std::string &stmt,
    const std::unordered_map<std::string, Value> &parameters) {
  if (client_ == nullptr) {
    return ExecutionResponse{ErrorCode::E_DISCONNECTED,
                             0,
                             nullptr,
                             nullptr,
                             std::make_unique<std::string>("Not open connection.")};
  }

  using TTransportException = apache::thrift::transport::TTransportException;
  ExecutionResponse resp;
  try {
    resp = client_->future_executeWithParameter(sessionId, stmt, parameters).get();
  } catch (const TTransportException &ex) {
    auto errType = ex.getType();
    std::string errMsg = ex.what();
    if (errType == TTransportException::END_OF_FILE ||
        (errType == TTransportException::INTERNAL_ERROR &&
         errMsg.find("Connection reset by peer") != std::string::npos)) {
      resp = ExecutionResponse{
          ErrorCode::E_FAIL_TO_CONNECT, 0, nullptr, nullptr, std::make_unique<std::string>(errMsg)};
    } else if (errType == TTransportException::TIMED_OUT) {
      resp = ExecutionResponse{
          ErrorCode::E_SESSION_TIMEOUT, 0, nullptr, nullptr, std::make_unique<std::string>(errMsg)};

    } else {
      resp = ExecutionResponse{
          ErrorCode::E_RPC_FAILURE, 0, nullptr, nullptr, std::make_unique<std::string>(errMsg)};
    }
  } catch (const std::exception &ex) {
    resp = ExecutionResponse{
        ErrorCode::E_RPC_FAILURE, 0, nullptr, nullptr, std::make_unique<std::string>(ex.what())};
  }

  return resp;
}

void Connection::asyncExecuteWithParameter(int64_t sessionId,
                                           const std::string &stmt,
                                           const std::unordered_map<std::string, Value> &parameters,
                                           ExecuteCallback cb) {
  if (client_ == nullptr) {
    cb(ExecutionResponse{ErrorCode::E_DISCONNECTED,
                         0,
                         nullptr,
                         nullptr,
                         std::make_unique<std::string>("Not open connection.")});
    return;
  }
  client_->future_executeWithParameter(sessionId, stmt, parameters)
      .thenValue([cb = std::move(cb)](auto &&resp) { cb(std::move(resp)); });
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

std::string Connection::executeJsonWithParameter(
    int64_t sessionId,
    const std::string &stmt,
    const std::unordered_map<std::string, Value> &parameters) {
  if (client_ == nullptr) {
    // TODO handle error
    return "";
  }

  std::string json;
  try {
    json = client_->future_executeJsonWithParameter(sessionId, stmt, parameters).get();
  } catch (const std::exception &ex) {
    // TODO handle error
    json = "";
  }

  return json;
}

void Connection::asyncExecuteJsonWithParameter(
    int64_t sessionId,
    const std::string &stmt,
    const std::unordered_map<std::string, Value> &parameters,
    ExecuteJsonCallback cb) {
  if (client_ == nullptr) {
    // TODO handle error
    cb("");
    return;
  }
  client_->future_executeJsonWithParameter(sessionId, stmt, parameters).thenValue(std::move(cb));
}

bool Connection::isOpen() {
  return ping();
}

void Connection::close() {
  if (client_ != nullptr) {
    clientLoopThread_->getEventBase()->runImmediatelyOrRunInEventBaseThreadAndWait(
        [this]() { delete client_; });
    client_ = nullptr;
  }
}

bool Connection::ping() {
  auto resp = execute(0 /*Only check connection*/, "YIELD 1");
  if (resp.errorCode == ErrorCode::E_FAIL_TO_CONNECT ||
      resp.errorCode == ErrorCode::E_DISCONNECTED) {
    DLOG(ERROR) << "Ping failed: " << *resp.errorMsg;
    return false;
  }
  return true;
}

void Connection::signout(int64_t sessionId) {
  if (client_ != nullptr) {
    client_->future_signout(sessionId).wait();
  }
}

VerifyClientVersionResp Connection::verifyClientVersion(const VerifyClientVersionReq &req) {
  if (client_ == nullptr) {
    return VerifyClientVersionResp{ErrorCode::E_DISCONNECTED,
                                   std::make_unique<std::string>("Not open connection.")};
  }
  try {
    return client_->future_verifyClientVersion(req).get();
  } catch (const std::exception &ex) {
    return VerifyClientVersionResp{ErrorCode::E_RPC_FAILURE,
                                   std::make_unique<std::string>(ex.what())};
  }
}

}  // namespace nebula
