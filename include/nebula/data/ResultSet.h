/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include "common/graph/Response.h"

namespace nebula {

class ResultSet {
public:
    explicit ResultSet(ExecutionResponse &&resp) : resp_(std::move(resp)) {}

    ErrorCode errorCode() const {
        return resp_.errorCode;
    }

    const DataSet *data() const {
        return resp_.data.get();
    }

    const PlanDescription *planDescription() const {
        return resp_.planDesc.get();
    }

    const std::string *errorMsg() const {
        return resp_.errorMsg.get();
    }

private:
    ExecutionResponse resp_;
};

}   // namespace nebula
