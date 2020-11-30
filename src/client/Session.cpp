/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include "nebula/client/Session.h"
#include "nebula/client/ConnectionPool.h"

namespace nebula {

ResultSet Session::execute(const std::string &stmt) {
    return ResultSet(conn_.execute(sessionId_, stmt));
}

void Session::asyncExecute(const std::string &stmt, ExecuteCallback cb) {
    conn_.asyncExecute(
        sessionId_, stmt, [cb = std::move(cb)](auto &&resp) { cb(ResultSet(std::move(resp))); });
}

std::string Session::executeJson(const std::string &stmt) {
    return conn_.executeJson(sessionId_, stmt);
}

void Session::asyncExecuteJson(const std::string &stmt, ExecuteJsonCallback cb) {
    conn_.asyncExecuteJson(
        sessionId_, stmt, [cb = std::move(cb)](auto &&json) { cb(std::move(json)); });
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

}   // namespace nebula
