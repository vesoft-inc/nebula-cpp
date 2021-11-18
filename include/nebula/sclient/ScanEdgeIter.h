/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <string>
#include <vector>

#include "common/datatypes/DataSet.h"

namespace nebula {
class StorageClient;

namespace storage {
namespace cpp2 {
class ScanEdgeRequest;
}  // namespace cpp2
}  // namespace storage

struct ScanEdgeIter {
    ScanEdgeIter(StorageClient* client,
                 storage::cpp2::ScanEdgeRequest* req,
                 bool hasNext = true);

    ~ScanEdgeIter();

    bool hasNext();

    DataSet next();

    StorageClient* client_;
    storage::cpp2::ScanEdgeRequest* req_;
    bool hasNext_;
    std::string nextCursor_;
};

}  // namespace nebula
