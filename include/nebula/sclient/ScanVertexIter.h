/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <string>
#include <vector>

#include "common/datatypes/DataSet.h"

namespace nebula {
namespace storage {
class GraphStorageClient;
namespace cpp2 {
class ScanVertexRequest;
}   // namespace cpp2
}   // namespace storage

struct ScanVertexIter {
    ScanVertexIter(storage::GraphStorageClient* client,
                   storage::cpp2::ScanVertexRequest* req,
                   bool hasNext = true)
        : client_(client), req_(req), hasNext_(hasNext) {}

    ScanVertexIter(const ScanVertexIter& rhs);

    ScanVertexIter(ScanVertexIter &&c) noexcept;

    ScanVertexIter& operator=(const ScanVertexIter& rhs);

    ScanVertexIter& operator=(ScanVertexIter&& rhs) noexcept;

    ~ScanVertexIter();

    bool hasNext() {
        return hasNext_;
    }

    DataSet next();

    storage::GraphStorageClient* client_;
    storage::cpp2::ScanVertexRequest* req_;
    bool hasNext_;
    std::string nextCursor_;
};

}   // namespace nebula
