/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>

#include "common/datatypes/HostAddr.h"
#include "nebula/sclient/ScanResultIter.h"

#define DEFAULT_LIMIT 1000
#define DEFAULT_START_TIME 0
#define DEFAULT_END_TIME std::numeric_limits<int64_t>::max()

namespace folly {
class IOThreadPoolExecutor;
}   // namespace folly

namespace nebula {

// Wrap the thrift client.
namespace meta {
class MetaClient;
}   // namespace meta

namespace storage {
class GraphStorageClient;
}   // namespace storage

using MetaHostAddr = HostAddr;

class StorageClient {
public:
    explicit StorageClient(const std::vector<nebula::MetaHostAddr> &metaServers);
    // disable copy
    StorageClient(const StorageClient &) = delete;
    StorageClient &operator=(const StorageClient &) = delete;

    StorageClient(StorageClient &&c) noexcept;

    ~StorageClient();

    StorageClient &operator=(StorageClient &&c) noexcept;

    ScanResultIter scanEdgeWithPart(std::string spaceName,
                                    int32_t partID,
                                    std::string edgeName,
                                    std::vector<std::string> propNames,
                                    int64_t limit = DEFAULT_LIMIT,
                                    int64_t startTime = DEFAULT_START_TIME,
                                    int64_t endTime = DEFAULT_END_TIME,
                                    std::string filter = "",
                                    bool onlyLatestVersion = false,
                                    bool enableReadFromFollower = true);

private:
    std::shared_ptr<folly::IOThreadPoolExecutor> ioExecutor_;
    std::unique_ptr<meta::MetaClient> mclient_;
    std::unique_ptr<storage::GraphStorageClient> sclient_;
};

}   // namespace nebula
