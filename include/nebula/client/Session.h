/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <common/datatypes/DataSet.h>

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
        session.retryConnect_ = true;
    }
    ~Session() {
        release();
    }

    ExecutionResponse execute(const std::string &stmt);

    void asyncExecute(const std::string &stmt, ExecuteCallback cb);

    std::string executeJson(const std::string &stmt);

    void asyncExecuteJson(const std::string &stmt, ExecuteJsonCallback cb);

    bool ping();

    void retryConnect();

    void release();

    bool valid() const {
        return sessionId_ > 0;
    }

    const std::string& timeZoneName() const {
        return timezoneName_;
    }

    int32_t timeZoneOffsetSecs() const {
        return offsetSecs_;
    }

    // convert the time to server time zone
    void toLocal(DataSet &data) {
        return toLocal(data, offsetSecs_);
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
    // auto retry connection
    bool retryConnect_{true};
};

}   // namespace nebula
