/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <folly/executors/IOThreadPoolExecutor.h>

#include "common/clients/meta/MetaClient.h"
#include "common/clients/storage/GraphStorageClient.h"

#include "nebula/sclient/StorageClient.h"

namespace nebula {

StorageClient::StorageClient(const std::vector<std::string> &metaServers) {
    for (const auto &addr : metaServers) {
        std::vector<std::string> ip_port;
        folly::split(':', addr, ip_port, true);
        CHECK(ip_port.size() == 2) << "meta server addr " << addr << " is illegal";
        metaServers_.emplace_back(ip_port[0], folly::to<int32_t>(ip_port[1]));
    }
    CHECK(!metaServers_.empty()) << "metaServers_ is empty";

    ioExecutor_ =
        std::make_shared<folly::IOThreadPoolExecutor>(std::thread::hardware_concurrency());
    mclient_ = std::make_unique<meta::MetaClient>(ioExecutor_, metaServers_);
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

VidType StorageClient::getSpaceVidType(std::string spaceName) {
    auto spaceIdResult = mclient_->getSpaceIdByNameFromCache(spaceName);
    if (!spaceIdResult.ok()) {
        LOG(ERROR) << "Get space id for " << spaceName << " failed: " << spaceIdResult.status();
        return VidType::UNKNOWN;
    }
    auto spaceId = spaceIdResult.value();

    auto spaceVidTypeResult = mclient_->getSpaceVidType(spaceId);
    if (!spaceVidTypeResult.ok()) {
        LOG(ERROR) << "Get space vid type for " << spaceName
                   << " failed: " << spaceVidTypeResult.status();
        return VidType::UNKNOWN;
    }
    auto spaceVidType = spaceVidTypeResult.value();
    if (spaceVidType == nebula::meta::cpp2::PropertyType::INT64) {
        return VidType::INT64;
    } else if (spaceVidType == nebula::meta::cpp2::PropertyType::FIXED_STRING) {
        return VidType::FIXED_STRING;
    } else {
        return VidType::UNKNOWN;
    }
}

int32_t StorageClient::getSpaceVidLen(std::string spaceName) {
    auto spaceIdResult = mclient_->getSpaceIdByNameFromCache(spaceName);
    if (!spaceIdResult.ok()) {
        LOG(ERROR) << "Get space id for " << spaceName << " failed: " << spaceIdResult.status();
        return -1;
    }
    auto spaceId = spaceIdResult.value();

    auto spaceVidLenResult = mclient_->getSpaceVidLen(spaceId);
    if (!spaceVidLenResult.ok()) {
        LOG(ERROR) << "Get space vid len for " << spaceName
                   << " failed: " << spaceVidLenResult.status();
        return -1;
    }
    return spaceVidLenResult.value();
}

std::vector<int32_t> StorageClient::getParts(std::string spaceName) {
    std::vector<int32_t> parts;

    auto partsAlloc = this->getPartsAlloc(spaceName);

    parts.reserve(partsAlloc.size());

    for (auto &partAlloc : partsAlloc) {
        parts.push_back(partAlloc.first);
    }
    return parts;
}

std::unordered_map<int32_t, std::vector<nebula::HostAddr>> StorageClient::getPartsAlloc(
    std::string spaceName) {
    std::unordered_map<int32_t, std::vector<nebula::HostAddr>> result;

    auto spaceIdResult = mclient_->getSpaceIdByNameFromCache(spaceName);
    if (!spaceIdResult.ok()) {
        LOG(ERROR) << "Get space id for " << spaceName << " failed: " << spaceIdResult.status();
        return result;
    }
    auto spaceId = spaceIdResult.value();

    auto partsAllocResult = mclient_->getPartsAlloc(spaceId).get();
    if (!partsAllocResult.ok()) {
        LOG(ERROR) << "Get parts alloc for space: " << spaceName
                   << " failed: " << partsAllocResult.status();
        return result;
    }
    result = partsAllocResult.value();
    return result;
}

std::unordered_map<int32_t, nebula::HostAddr> StorageClient::getPartsLeader(std::string spaceName) {
    std::unordered_map<int32_t, nebula::HostAddr> result;

    auto spaceIdResult = mclient_->getSpaceIdByNameFromCache(spaceName);
    if (!spaceIdResult.ok()) {
        LOG(ERROR) << "Get space id for " << spaceName << " failed: " << spaceIdResult.status();
        return result;
    }
    auto spaceId = spaceIdResult.value();

    auto partsAllocResult = mclient_->getPartsAlloc(spaceId).get();
    if (!partsAllocResult.ok()) {
        LOG(ERROR) << "Get parts alloc for space: " << spaceName
                   << " failed: " << partsAllocResult.status();
        return result;
    }
    auto partsAlloc = partsAllocResult.value();
    for (auto &partAlloc : partsAlloc) {
        auto partId = partAlloc.first;
        auto leaderResult = sclient_->getLeader(spaceId, partId);
        if (!leaderResult.ok()) {
            LOG(ERROR) << "Get leader host for space: " << spaceName << ", part: " << partId
                       << " failed: " << leaderResult.status();
            return result;
        }
        result[partId] = leaderResult.value();
    }
    DCHECK(result.size() == partsAlloc.size());

    return result;
}

ScanEdgeIter StorageClient::scanEdgeWithPart(std::string spaceName,
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
        return ScanEdgeIter(nullptr, nullptr, false);
    }
    int32_t spaceId = spaceIdResult.value();
    auto edgeTypeResult = mclient_->getEdgeTypeByNameFromCache(spaceId, edgeName);
    if (!edgeTypeResult.ok()) {
        LOG(ERROR) << "Get edge type for " << edgeName << " failed: " << edgeTypeResult.status();
        return ScanEdgeIter(nullptr, nullptr, false);
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

    return ScanEdgeIter(sclient_.get(), req);
}

ScanVertexIter StorageClient::scanVertexWithPart(std::string spaceName,
                                                 int32_t partId,
                                                 std::string tagName,
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
        return ScanVertexIter(nullptr, nullptr, false);
    }
    int32_t spaceId = spaceIdResult.value();
    auto tagIdResult = mclient_->getTagIDByNameFromCache(spaceId, tagName);
    if (!tagIdResult.ok()) {
        LOG(ERROR) << "Get tag id for " << tagName << " failed: " << tagIdResult.status();
        return ScanVertexIter(nullptr, nullptr, false);
    }
    int32_t tagId = tagIdResult.value();

    storage::cpp2::VertexProp returnCols;
    returnCols.set_tag(tagId);
    returnCols.set_props(propNames);

    auto *req = new storage::cpp2::ScanVertexRequest;
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

    return ScanVertexIter(sclient_.get(), req);
}

}   // namespace nebula
