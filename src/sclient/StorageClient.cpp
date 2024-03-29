/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "nebula/sclient/StorageClient.h"

#include <folly/executors/IOThreadPoolExecutor.h>

#include "../thrift/ThriftClientManager.h"
#include "interface/gen-cpp2/GraphStorageServiceAsyncClient.h"
#include "interface/gen-cpp2/storage_types.h"

namespace nebula {

StorageClient::StorageClient(const std::vector<std::string>& metaAddrs,
                             const MConfig& mConfig,
                             const SConfig& sConfig) {
  mClient_ = std::make_unique<MetaClient>(metaAddrs, mConfig);
  sConfig_ = sConfig;
  ioExecutor_ = std::make_shared<folly::IOThreadPoolExecutor>(std::thread::hardware_concurrency());
  clientsMan_ =
      std::make_shared<thrift::ThriftClientManager<storage::cpp2::GraphStorageServiceAsyncClient>>(
          sConfig.connTimeoutInMs_, sConfig.enableSSL_, sConfig.CAPath_);
}

StorageClient::~StorageClient() = default;

std::vector<PartitionID> StorageClient::getParts(const std::string& spaceName) {
  auto spaceIdResult = mClient_->getSpaceIdByNameFromCache(spaceName);
  if (!spaceIdResult.first) {
    LOG(ERROR) << "Get space id from cache for space name " << spaceName << " failed";
    return {};
  }
  int32_t spaceId = spaceIdResult.second;
  auto ret = mClient_->getPartsFromCache(spaceId);
  if (!ret.first) {
    LOG(ERROR) << "Get parts from cache for space id " << spaceId << " failed";
    return {};
  }
  return ret.second;
}

ScanEdgeIter StorageClient::scanEdgeWithPart(std::string spaceName,
                                             PartitionID partId,
                                             std::string edgeName,
                                             std::vector<std::string> propNames,
                                             int64_t limit,
                                             int64_t startTime,
                                             int64_t endTime,
                                             std::string filter,
                                             bool onlyLatestVersion,
                                             bool enableReadFromFollower,
                                             bool needAuth,
                                             std::string username,
                                             std::string password) {
  auto spaceIdResult = mClient_->getSpaceIdByNameFromCache(spaceName);
  if (!spaceIdResult.first) {
    return {nullptr, nullptr, false};
  }
  int32_t spaceId = spaceIdResult.second;
  auto edgeTypeResult = mClient_->getEdgeTypeByNameFromCache(spaceId, edgeName);
  if (!edgeTypeResult.first) {
    return {nullptr, nullptr, false};
  }
  int32_t edgeType = edgeTypeResult.second;

  storage::cpp2::EdgeProp returnCols;
  returnCols.set_type(edgeType);
  returnCols.set_props(propNames);

  auto* req = new storage::cpp2::ScanEdgeRequest;
  req->set_space_id(spaceId);
  // old interface
  // req->set_part_id(partId);
  // req->set_cursor("");
  // new interface
  storage::cpp2::ScanCursor scanCursor;
  req->set_parts(std::unordered_map<PartitionID, storage::cpp2::ScanCursor>{{partId, scanCursor}});
  req->set_return_columns({returnCols});
  req->set_limit(limit);
  req->set_start_time(startTime);
  req->set_end_time(endTime);
  req->set_filter(filter);
  req->set_only_latest_version(onlyLatestVersion);
  req->set_enable_read_from_follower(enableReadFromFollower);
  req->set_need_authenticate(needAuth);
  req->set_username(username);
  req->set_password(password);

  return {this, req};
}

std::pair<::nebula::ErrorCode, storage::cpp2::ScanResponse> StorageClient::doScanEdge(
    const storage::cpp2::ScanEdgeRequest& req) {
  std::pair<HostAddr, storage::cpp2::ScanEdgeRequest> request;
  auto partCursorMap = req.get_parts();
  DCHECK_EQ(partCursorMap.size(), 1);
  PartitionID partId = partCursorMap.begin()->first;
  auto host = mClient_->getPartLeaderFromCache(req.get_space_id(), partId);
  if (!host.first) {
    return {::nebula::ErrorCode::E_UNKNOWN, storage::cpp2::ScanResponse()};
  }
  request.first = host.second;
  request.second = req;

  folly::Promise<std::pair<::nebula::ErrorCode, storage::cpp2::ScanResponse>> promise;
  auto future = promise.getFuture();
  getResponse(
      std::move(request),
      [](storage::cpp2::GraphStorageServiceAsyncClient* client,
         const storage::cpp2::ScanEdgeRequest& r) { return client->future_scanEdge(r); },
      std::move(promise));
  return std::move(future).get();
}

ScanVertexIter StorageClient::scanVertexWithPart(
    std::string spaceName,
    int32_t partId,
    // tag name -> prop names
    std::unordered_map<std::string, std::vector<std::string>> tagProps,
    int64_t limit,
    int64_t startTime,
    int64_t endTime,
    std::string filter,
    bool onlyLatestVersion,
    bool enableReadFromFollower,
    bool needAuth,
    std::string username,
    std::string password) {
  auto spaceIdResult = mClient_->getSpaceIdByNameFromCache(spaceName);
  if (!spaceIdResult.first) {
    return {nullptr, nullptr, false};
  }
  int32_t spaceId = spaceIdResult.second;

  std::vector<storage::cpp2::VertexProp> returnCols;

  for (const auto& tagProp : tagProps) {
    auto tagTypeResult = mClient_->getTagIdByNameFromCache(spaceId, tagProp.first);
    if (!tagTypeResult.first) {
      return {nullptr, nullptr, false};
    }
    int32_t tagType = tagTypeResult.second;

    storage::cpp2::VertexProp returnCol;
    returnCol.set_tag(tagType);
    returnCol.set_props(tagProp.second);
    returnCols.emplace_back(returnCol);
  }

  auto* req = new storage::cpp2::ScanVertexRequest;
  req->set_space_id(spaceId);
  // old interface
  // req->set_part_id(partId);
  // req->set_cursor("");
  // new interface
  storage::cpp2::ScanCursor scanCursor;
  req->set_parts(std::unordered_map<PartitionID, storage::cpp2::ScanCursor>{{partId, scanCursor}});
  req->set_return_columns(std::move(returnCols));
  req->set_limit(limit);
  req->set_start_time(startTime);
  req->set_end_time(endTime);
  req->set_filter(filter);
  req->set_only_latest_version(onlyLatestVersion);
  req->set_enable_read_from_follower(enableReadFromFollower);
  req->set_need_authenticate(needAuth);
  req->set_username(username);
  req->set_password(password);

  return {this, req};
}

std::pair<::nebula::ErrorCode, storage::cpp2::ScanResponse> StorageClient::doScanVertex(
    const storage::cpp2::ScanVertexRequest& req) {
  std::pair<HostAddr, storage::cpp2::ScanVertexRequest> request;
  auto partCursorMap = req.get_parts();
  DCHECK_EQ(partCursorMap.size(), 1);
  PartitionID partId = partCursorMap.begin()->first;
  auto host = mClient_->getPartLeaderFromCache(req.get_space_id(), partId);
  if (!host.first) {
    return {::nebula::ErrorCode::E_UNKNOWN, storage::cpp2::ScanResponse()};
  }
  request.first = host.second;
  request.second = req;

  folly::Promise<std::pair<::nebula::ErrorCode, storage::cpp2::ScanResponse>> promise;
  auto future = promise.getFuture();
  getResponse(
      std::move(request),
      [](storage::cpp2::GraphStorageServiceAsyncClient* client,
         const storage::cpp2::ScanVertexRequest& r) { return client->future_scanVertex(r); },
      std::move(promise));
  return std::move(future).get();
}

template <typename Request, typename RemoteFunc, typename Response>
void StorageClient::getResponse(std::pair<HostAddr, Request>&& request,
                                RemoteFunc&& remoteFunc,
                                folly::Promise<std::pair<::nebula::ErrorCode, Response>> pro) {
  auto* evb = DCHECK_NOTNULL(ioExecutor_)->getEventBase();
  folly::via(
      evb,
      [evb,
       request = std::move(request),
       remoteFunc = std::move(remoteFunc),
       pro = std::move(pro),
       this]() mutable {
        auto host = request.first;
        auto client = clientsMan_->client(host, evb, false, sConfig_.clientTimeoutInMs_);
        LOG(INFO) << "Send request to storage " << host;
        remoteFunc(client.get(), request.second)
            .via(evb)
            .thenValue([pro = std::move(pro)](Response&& resp) mutable {
              auto& result = resp.get_result();
              for (auto& part : result.get_failed_parts()) {
                auto partId = part.get_part_id();
                auto code = part.get_code();

                LOG(ERROR) << "Failure! Failed part: " << partId
                           << ", error code: " << static_cast<int32_t>(code);
                pro.setValue(
                    std::make_pair(::nebula::ErrorCode(static_cast<int32_t>(code)), Response()));
                return;
              }
              pro.setValue(std::make_pair(::nebula::ErrorCode::SUCCEEDED, std::move(resp)));
              return;
            })
            .thenError([pro = std::move(pro), host](folly::exception_wrapper&& exWrapper) mutable {
              using TransportException = apache::thrift::transport::TTransportException;
              auto ex = exWrapper.get_exception<TransportException>();
              if (ex) {
                if (ex->getType() == TransportException::TIMED_OUT) {
                  LOG(ERROR) << "Request to " << host << " time out: " << ex->what();
                } else {
                  LOG(ERROR) << "Request to " << host << " failed: " << ex->what();
                }
              } else {
                LOG(ERROR) << "Request to " << host << " failed.";
              }
              pro.setValue(std::make_pair(::nebula::ErrorCode::E_RPC_FAILURE, Response()));
              return;
            });
      });  // via
}

}  // namespace nebula
