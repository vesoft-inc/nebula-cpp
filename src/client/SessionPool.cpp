// Copyright (c) 2022 vesoft inc. All rights reserved.
//
// This source code is licensed under Apache 2.0 License.

#include "nebula/client/SessionPool.h"

#include <folly/json.h>

#include "common/time/TimeConversion.h"
#include "nebula/client/ConnectionPool.h"

namespace nebula {

ExecutionResponse SessionPool::execute(const std::string &stmt) {
  auto result = getIdleSession();
  if (result.second) {
    auto resp = result.first.execute(stmt);
    if (*resp.spaceName != config_.spaceName_) {
      // switch to origin space
      result.first.execute("USE " + config_.spaceName_);
    }
    giveBack(std::move(result.first));
    return resp;
  } else {
    return ExecutionResponse{ErrorCode::E_DISCONNECTED,
                             0,
                             nullptr,
                             nullptr,
                             std::make_unique<std::string>("No idle session.")};
  }
}

ExecutionResponse SessionPool::executeWithParameter(
    const std::string &stmt, const std::unordered_map<std::string, Value> &parameters) {
  auto result = getIdleSession();
  if (result.second) {
    auto resp = result.first.executeWithParameter(stmt, parameters);
    if (*resp.spaceName != config_.spaceName_) {
      // switch to origin space
      result.first.execute("USE " + config_.spaceName_);
    }
    giveBack(std::move(result.first));
    return resp;
  } else {
    return ExecutionResponse{ErrorCode::E_DISCONNECTED,
                             0,
                             nullptr,
                             nullptr,
                             std::make_unique<std::string>("No idle session.")};
  }
}

std::string SessionPool::executeJson(const std::string &stmt) {
  auto result = getIdleSession();
  if (result.second) {
    auto resp = result.first.executeJson(stmt);
    auto obj = folly::parseJson(resp);
    if (obj["spaceName"].asString() != config_.spaceName_) {
      // switch to origin space
      result.first.execute("USE " + config_.spaceName_);
    }
    giveBack(std::move(result.first));
    return resp;
  } else {
    // TODO handle error
    return "";
  }
}

std::string SessionPool::executeJsonWithParameter(
    const std::string &stmt, const std::unordered_map<std::string, Value> &parameters) {
  auto result = getIdleSession();
  if (result.second) {
    auto resp = result.first.executeJsonWithParameter(stmt, parameters);
    auto obj = folly::parseJson(resp);
    if (obj["spaceName"].asString() != config_.spaceName_) {
      // switch to origin space
      result.first.execute("USE " + config_.spaceName_);
    }
    giveBack(std::move(result.first));
    return resp;
  } else {
    // TODO handle error
    return "";
  }
}

}  // namespace nebula
