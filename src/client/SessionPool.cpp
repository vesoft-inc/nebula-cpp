// Copyright (c) 2022 vesoft inc. All rights reserved.
//
// This source code is licensed under Apache 2.0 License.

#include "nebula/client/SessionPool.h"

#include <folly/json.h>

#include "common/graph/Response.h"
#include "common/time/TimeConversion.h"
#include "nebula/client/ConnectionPool.h"

namespace nebula {

bool SessionPool::init() {
  Config conf;
  conf.maxConnectionPoolSize_ = config_.maxSize_;
  conf.minConnectionPoolSize_ = config_.minSize_;
  conf.idleTime_ = config_.idleTime_;
  conf.timeout_ = config_.timeout_;
  pool_->init(config_.addrs_, conf);
  if (config_.spaceName_.empty()) {
    return false;
  }
  if (config_.username_.empty() || config_.password_.empty()) {
    return false;
  }
  std::string useSpace = "USE " + config_.spaceName_;
  for (std::size_t i = 0; i < config_.maxSize_; ++i) {
    // use space
    auto session = pool_->getSession(config_.username_, config_.password_);
    auto resp = session.execute(useSpace);
    if (resp.errorCode == ErrorCode::SUCCEEDED) {
      idleSessions_.emplace_back(std::move(session));
    } else {
      return false;
    }
  }
  return true;
}

ExecutionResponse SessionPool::execute(const std::string &stmt) {
  return executeWithParameter(stmt, {});
}

ExecutionResponse SessionPool::executeWithParameter(
    const std::string &stmt, const std::unordered_map<std::string, Value> &parameters) {
  auto result = getIdleSession();
  if (result.second) {
    auto resp = result.first.executeWithParameter(stmt, parameters);
    if (resp.spaceName != nullptr && *resp.spaceName != config_.spaceName_) {
      if (*resp.spaceName == "") {
        // This can be caused by reconnect, switch to origin space and try to query again
        resp =
            result.first.executeWithParameter("USE " + config_.spaceName_ + ";" + stmt, parameters);
      } else {
        // switch to origin space only
        result.first.execute("USE " + config_.spaceName_);
      }
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
  return executeJsonWithParameter(stmt, {});
}

std::string SessionPool::executeJsonWithParameter(
    const std::string &stmt, const std::unordered_map<std::string, Value> &parameters) {
  auto result = getIdleSession();
  if (result.second) {
    auto resp = result.first.executeJsonWithParameter(stmt, parameters);
    auto obj = folly::parseJson(resp);
    auto respSpaceName = obj["results"][0]["spaceName"].asString();
    if (respSpaceName != config_.spaceName_) {
      if (respSpaceName == "") {
        // This can be caused by reconnect, switch to origin space and try to query again
        resp = result.first.executeJsonWithParameter("USE " + config_.spaceName_ + ";" + stmt,
                                                     parameters);
      } else {
        // switch to origin space only
        result.first.execute("USE " + config_.spaceName_);
      }
    }
    giveBack(std::move(result.first));
    return resp;
  } else {
    // TODO handle error
    return "";
  }
}

}  // namespace nebula
