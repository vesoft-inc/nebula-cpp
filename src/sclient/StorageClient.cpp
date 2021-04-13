/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <memory>
#include <thread>

#include <folly/executors/IOThreadPoolExecutor.h>

#include "common/clients/meta/MetaClient.h"
#include "common/clients/storage/GraphStorageClient.h"

#include "nebula/sclient/StorageClient.h"

namespace nebula {

StorageClient::StorageClient(const std::vector<MetaHostAddr> &metaServers) {
    ioExecutor_ = std::make_shared<folly::IOThreadPoolExecutor>(
                        std::thread::hardware_concurrency());
    mclient_ = std::make_unique<meta::MetaClient>(ioExecutor_, metaServers);
    // load data try 3 time
    bool loadDataOk = mclient_->waitForMetadReady(3);
    if (!loadDataOk) {
        // Resort to retrying in the background
        LOG(WARNING) << "Failed to synchronously wait for meta service ready";
    }
    sclient_ = std::make_unique<storage::GraphStorageClient>(ioExecutor_, mclient_.get());
}

StorageClient::StorageClient(StorageClient &&c) noexcept {
    ioExecutor_ = std::move(c.ioExecutor_);
    mclient_.reset(c.mclient_.release());
    sclient_.reset(c.sclient_.release());
}

StorageClient::~StorageClient() = default;

StorageClient &StorageClient::operator=(StorageClient &&rhs) noexcept {
    ioExecutor_ = std::move(rhs.ioExecutor_);
    mclient_ = std::move(rhs.mclient_);
    sclient_ = std::move(rhs.sclient_);
    return *this;
}

ScanResultIter StorageClient::scanEdgeWithPart(std::string spaceName,
                                           int32_t partId,
                                           std::string edgeName,
                                           std::vector<std::string> propNames,
                                           int64_t limit,
                                           int64_t startTime,
                                           int64_t endTime,
                                           std::string filter,
                                           bool onlyLatestVersion,
                                           bool enableReadFromFollower) {
    auto spaceIdResult = mclient_->getSpaceIdByNameFromCache(spaceName);
    if (!spaceIdResult.ok()) {
        LOG(ERROR) << "Get space id for " << spaceName << " failed: " << spaceIdResult.status();
        return ScanResultIter(nullptr, nullptr, false);
    }
    int32_t spaceId = spaceIdResult.value();
    auto edgeTypeResult = mclient_->getEdgeTypeByNameFromCache(spaceId, edgeName);
    if (!edgeTypeResult.ok()) {
        LOG(ERROR) << "Get edge type for " << edgeName << " failed: " << edgeTypeResult.status();
        return ScanResultIter(nullptr, nullptr, false);
    }
    int32_t edgeType = edgeTypeResult.value();

    storage::cpp2::EdgeProp returnCols;
    returnCols.set_type(edgeType);
    returnCols.set_props(propNames);

    auto *req = new storage::cpp2::ScanEdgeRequest;
    req->set_space_id(spaceId);
    req->set_part_id(partId);
    req->set_cursor("");
    req->set_return_columns(returnCols);
    req->set_limit(limit);
    req->set_start_time(startTime);
    req->set_end_time(endTime);
    req->set_filter(filter);
    req->set_only_latest_version(onlyLatestVersion);
    req->set_enable_read_from_follower(enableReadFromFollower);

    return ScanResultIter(sclient_.get(), req);
}

}   // namespace nebula
