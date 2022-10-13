// Copyright (c) 2022 vesoft inc. All rights reserved.
//
// This source code is licensed under Apache 2.0 License.

#pragma once

#include <common/datatypes/DataSet.h>

#include <cassert>
#include <cstddef>
#include <mutex>

#include "nebula/client/Config.h"
#include "nebula/client/ConnectionPool.h"
#include "nebula/client/Session.h"

namespace nebula {

struct SessionPoolConfig {
  std::string username_;
  std::string password_;
  std::vector<std::string> addrs_;  // the list of graph addresses
  std::string spaceName_;
  // Socket timeout and Socket connection timeout, unit: seconds
  std::uint32_t timeout_{0};
  // The idleTime of the connection, unit: seconds
  // If connection's idle time is longer than idleTime, it will be delete
  // 0 value means the connection will not expire
  std::uint32_t idleTime_{0};
  std::uint32_t maxSize_{10};  // max size of the session pool. should be adjusted according to the
                               // max threads will be using.
  std::uint32_t minSize_{0};   // min size of  the session pool
};

class SessionPool {
 public:
  SessionPool() = delete;
  explicit SessionPool(SessionPoolConfig config)
      : config_(std::move(config)), pool_(new ConnectionPool()) {}
  SessionPool(const SessionPool &) = delete;  // no copy
  SessionPool(SessionPool &&pool)
      : config_(std::move(pool.config_)), pool_(std::move(pool.pool_)) {}

  // initialize session and context
  // return false when failed, otherwise return true
  // When return false, the pool is in invalid state, user must destruct it
  // instead of continue.
  bool init() {
    Config conf;
    conf.maxConnectionPoolSize_ = config_.maxSize_;
    conf.minConnectionPoolSize_ = config_.minSize_;
    conf.idleTime_ = config_.idleTime_;
    conf.timeout_ = config_.timeout_;
    pool_->init(config_.addrs_, conf);
    if (config_.spaceName_.empty()) {
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

  // Session pool use fixed space, don't switch space when execute
  ExecutionResponse execute(const std::string &stmt);

  ExecutionResponse executeWithParameter(const std::string &stmt,
                                         const std::unordered_map<std::string, Value> &parameters);

  std::string executeJson(const std::string &stmt);

  std::string executeJsonWithParameter(const std::string &stmt,
                                       const std::unordered_map<std::string, Value> &parameters);

 private:
  std::pair<Session, bool> getIdleSession() {
    std::lock_guard<std::mutex> l(m_);
    if (idleSessions_.empty()) {
      return std::make_pair(Session(), false);
    }
    auto session = std::move(idleSessions_.front());
    idleSessions_.pop_front();
    return std::make_pair(std::move(session), true);
  }

  void giveBack(Session &&session) {
    std::lock_guard<std::mutex> l(m_);
    idleSessions_.emplace_back(std::move(session));
  }

  SessionPoolConfig config_;
  std::unique_ptr<ConnectionPool> pool_;
  // destruct session before pool
  std::mutex m_;
  std::list<Session> idleSessions_;
};

}  // namespace nebula
