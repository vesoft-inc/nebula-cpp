/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <common/datatypes/DataSet.h>

#include <atomic>

#include "nebula/client/Connection.h"

namespace nebula {

class ConnectionPool;

class Session {
 public:
  using ExecuteCallback = std::function<void(ExecutionResponse &&)>;
  using ExecuteJsonCallback = std::function<void(std::string &&)>;

  Session() = default;
  Session(int64_t sessionId,
          Connection &&conn,
          ConnectionPool *pool,
          const std::string &username,
          const std::string &password,
          const std::string &timezoneName,
          int32_t offsetSecs,
          bool retryConnect)
      : sessionId_(sessionId),
        conn_(std::move(conn)),
        pool_(pool),
        username_(username),
        password_(password),
        timezoneName_(timezoneName),
        offsetSecs_(offsetSecs),
        retryConnect_(retryConnect) {}
  Session(const Session &) = delete;  // no copy
  Session(Session &&session)
      : sessionId_(session.sessionId_),
        conn_(std::move(session.conn_)),
        pool_(session.pool_),
        username_(std::move(session.username_)),
        password_(std::move(session.password_)),
        timezoneName_(std::move(session.timezoneName_)),
        offsetSecs_(session.offsetSecs_),
        retryConnect_(session.retryConnect_) {
    session.sessionId_ = -1;
    session.pool_ = nullptr;
    session.offsetSecs_ = 0;
  }
  void operator=(Session &&session) {
    sessionId_ = session.sessionId_;
    username_ = std::move(session.username_);
    password_ = std::move(session.password_);
    timezoneName_ = std::move(session.timezoneName_);
    offsetSecs_ = session.offsetSecs_;
    session.sessionId_ = -1;
    session.pool_ = nullptr;
    session.offsetSecs_ = 0;
  }
  ~Session() {
    release();
  }

  ExecutionResponse execute(const std::string &stmt);

  void asyncExecute(const std::string &stmt, ExecuteCallback cb);

  ExecutionResponse executeWithParameter(const std::string &stmt,
                                         const std::unordered_map<std::string, Value> &parameters);

  void asyncExecuteWithParameter(const std::string &stmt,
                                 const std::unordered_map<std::string, Value> &parameters,
                                 ExecuteCallback cb);

  std::string executeJson(const std::string &stmt);

  void asyncExecuteJson(const std::string &stmt, ExecuteJsonCallback cb);

  std::string executeJsonWithParameter(const std::string &stmt,
                                       const std::unordered_map<std::string, Value> &parameters);

  void asyncExecuteJsonWithParameter(const std::string &stmt,
                                     const std::unordered_map<std::string, Value> &parameters,
                                     ExecuteJsonCallback cb);

  bool ping();

  ErrorCode retryConnect();

  void release();

  bool valid() const {
    return sessionId_ > 0;
  }

  const std::string &timeZoneName() const {
    return timezoneName_;
  }

  int32_t timeZoneOffsetSecs() const {
    return offsetSecs_;
  }

  // convert the time to server time zone
  void toLocal(DataSet &data) {
    return toLocal(data, offsetSecs_);
  }

  static bool isSessionError(const ExecutionResponse &resp) {
    return resp.errorCode == ErrorCode::E_SESSION_INVALID ||
           resp.errorCode == ErrorCode::E_SESSION_NOT_FOUND ||
           resp.errorCode == ErrorCode::E_SESSION_TIMEOUT;
  }

  // convert the time to specific time zone
  static void toLocal(DataSet &data, int32_t offsetSecs);

 private:
  int64_t sessionId_{-1};
  Connection conn_;
  ConnectionPool *pool_{nullptr};
  std::string username_;
  std::string password_;
  // empty means not a named timezone
  std::string timezoneName_;
  int32_t offsetSecs_;
  bool retryConnect_{true};
  std::atomic<bool> connectionIsBroken_{false};
};

}  // namespace nebula
