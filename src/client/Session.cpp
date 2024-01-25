/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "nebula/client/Session.h"

#include "common/graph/Response.h"
#include "common/time/TimeConversion.h"
#include "nebula/client/ConnectionPool.h"

namespace nebula {

ExecutionResponse Session::execute(const std::string &stmt) {
  return executeWithParameter(stmt, {});
}

void Session::asyncExecute(const std::string &stmt, ExecuteCallback cb) {
  conn_.asyncExecute(sessionId_, stmt, [cb = std::move(cb)](auto &&resp) {
    cb(ExecutionResponse(std::move(resp)));
  });
}

ExecutionResponse Session::executeWithParameter(
    const std::string &stmt, const std::unordered_map<std::string, Value> &parameters) {
  if (connectionIsBroken_ && retryConnect_) {
    if (retryConnect() == nebula::ErrorCode::SUCCEEDED) {
      return ExecutionResponse(conn_.executeWithParameter(sessionId_, stmt, parameters));
    } else {
      return ExecutionResponse{ErrorCode::E_RPC_FAILURE,
                               0,
                               nullptr,
                               nullptr,
                               std::make_unique<std::string>("All servers are broken.")};
    }
  }
  auto resp = conn_.executeWithParameter(sessionId_, stmt, parameters);
  if (resp.errorCode == nebula::ErrorCode::SUCCEEDED) {
    return resp;
  } else if (resp.errorCode == nebula::ErrorCode::E_FAIL_TO_CONNECT || isSessionError(resp)) {
    connectionIsBroken_ = true;
    if (retryConnect_) {
      if (retryConnect() == nebula::ErrorCode::SUCCEEDED) {
        connectionIsBroken_ = false;
        return ExecutionResponse(conn_.executeWithParameter(sessionId_, stmt, parameters));
      } else {
        connectionIsBroken_ = true;
        return ExecutionResponse{ErrorCode::E_RPC_FAILURE,
                                 0,
                                 nullptr,
                                 nullptr,
                                 std::make_unique<std::string>("All servers are broken.")};
      }
    }
  }
  return resp;
}

void Session::asyncExecuteWithParameter(const std::string &stmt,
                                        const std::unordered_map<std::string, Value> &parameters,
                                        ExecuteCallback cb) {
  conn_.asyncExecuteWithParameter(sessionId_, stmt, parameters, [cb = std::move(cb)](auto &&resp) {
    cb(ExecutionResponse(std::move(resp)));
  });
}

std::string Session::executeJson(const std::string &stmt) {
  return conn_.executeJson(sessionId_, stmt);
}

void Session::asyncExecuteJson(const std::string &stmt, ExecuteJsonCallback cb) {
  conn_.asyncExecuteJson(
      sessionId_, stmt, [cb = std::move(cb)](auto &&json) { cb(std::move(json)); });
}

std::string Session::executeJsonWithParameter(
    const std::string &stmt, const std::unordered_map<std::string, Value> &parameters) {
  return conn_.executeJsonWithParameter(sessionId_, stmt, parameters);
}

void Session::asyncExecuteJsonWithParameter(
    const std::string &stmt,
    const std::unordered_map<std::string, Value> &parameters,
    ExecuteJsonCallback cb) {
  conn_.asyncExecuteJsonWithParameter(
      sessionId_, stmt, parameters, [cb = std::move(cb)](auto &&json) { cb(std::move(json)); });
}

bool Session::ping() {
  return conn_.ping();
}

ErrorCode Session::retryConnect() {
  pool_->giveBack(std::move(conn_));
  conn_ = pool_->getConnection();
  auto resp = conn_.authenticate(username_, password_);
  sessionId_ = resp.sessionId != nullptr ? *resp.sessionId : -1;
  return resp.errorCode;
}

void Session::release() {
  if (valid()) {
    conn_.signout(sessionId_);
    pool_->giveBack(std::move(conn_));
    sessionId_ = -1;
  }
}

void Session::toLocal(DataSet &data, int32_t offsetSecs) {
  for (auto &row : data.rows) {
    for (auto &col : row.values) {
      if (col.isTime()) {
        col.setTime(time::TimeConversion::timeShift(col.getTime(), offsetSecs));
      } else if (col.isDateTime()) {
        col.setDateTime(time::TimeConversion::dateTimeShift(col.getDateTime(), offsetSecs));
      }
    }
  }
}

}  // namespace nebula
