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
class ScanEdgeRequest;
}   // namespace cpp2
}   // namespace storage

struct ScanEdgeIter {
    ScanEdgeIter(storage::GraphStorageClient* client,
                 storage::cpp2::ScanEdgeRequest* req,
                 bool hasNext = true)
        : client_(client), req_(req), hasNext_(hasNext) {}

    ScanEdgeIter(const ScanEdgeIter& rhs);

    ScanEdgeIter(ScanEdgeIter&& c);

    ScanEdgeIter& operator=(const ScanEdgeIter& rhs);

    ScanEdgeIter& operator=(ScanEdgeIter&& rhs) noexcept;

    ~ScanEdgeIter();

    bool hasNext() {
        return hasNext_;
    }

    DataSet next();

    storage::GraphStorageClient* client_;
    storage::cpp2::ScanEdgeRequest* req_;
    bool hasNext_;
    std::string nextCursor_;
};

}   // namespace nebula
