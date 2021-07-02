/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <common/time/TimeConversion.h>

#include "nebula/client/Session.h"
#include "nebula/client/ConnectionPool.h"

namespace nebula {

ExecutionResponse Session::execute(const std::string &stmt) {
    auto resp = conn_.execute(sessionId_, stmt);
    if (resp.errorCode == ErrorCode::E_RPC_FAILURE && retryConnect_) {
        auto errorCode = retryConnect();
        if (errorCode == ErrorCode::E_RPC_FAILURE) {
            return ExecutionResponse{errorCode,
                                     0,
                                     nullptr,
                                     nullptr,
                                     std::make_unique<std::string>("Retry connect failed.")};
        }
        return execute(stmt);
    } else {
        return resp;
    }
}

void Session::asyncExecute(const std::string &stmt, ExecuteCallback cb) {
    conn_.asyncExecute(sessionId_, stmt, [this, stmt, cb = std::move(cb)](auto &&resp) {
        if (resp.errorCode == ErrorCode::E_RPC_FAILURE && retryConnect_) {
            auto errorCode = retryConnect();
            if (errorCode != ErrorCode::SUCCEEDED) {
                cb(ExecutionResponse{errorCode,
                                     0,
                                     nullptr,
                                     nullptr,
                                     std::make_unique<std::string>("Retry connect failed.")});
                return;
            }
            asyncExecute(stmt, std::move(cb));
        } else {
            cb(std::move(resp));
        }
    });
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
    conn_.signout(sessionId_);
    if (!conn_.open()) {
        return ErrorCode::E_DISCONNECTED;
    }
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

}   // namespace nebula
