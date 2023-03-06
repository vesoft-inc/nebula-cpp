/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */
#include "nebula/mclient/MetaClient.h"

#include <folly/executors/IOThreadPoolExecutor.h>

#include <functional>

#include "../thrift/ThriftClientManager.h"
#include "common/thrift/ThriftTypes.h"
#include "interface/gen-cpp2/MetaServiceAsyncClient.h"
#include "interface/gen-cpp2/meta_types.h"

namespace nebula {

MetaClient::MetaClient(const std::vector<std::string>& metaAddrs, const MConfig& mConfig) {
  for (const auto& addr : metaAddrs) {
    std::vector<std::string> ip_port;
    folly::split(':', addr, ip_port, true);
    CHECK(ip_port.size() == 2) << "meta server addr " << addr << " is illegal";
    metaAddrs_.emplace_back(ip_port[0], folly::to<int32_t>(ip_port[1]));
  }
  CHECK(!metaAddrs_.empty()) << "metaAddrs_ is empty";
  mConfig_ = mConfig;

  ioExecutor_ = std::make_shared<folly::IOThreadPoolExecutor>(std::thread::hardware_concurrency());
  clientsMan_ = std::make_shared<thrift::ThriftClientManager<meta::cpp2::MetaServiceAsyncClient>>(
      mConfig_.connTimeoutInMs_, mConfig_.enableSSL_, mConfig_.CAPath_);
  bool b = loadData();  // load data into cache
  if (!b) {
    LOG(ERROR) << "load data failed";
  }
}

MetaClient::~MetaClient() = default;

std::pair<bool, GraphSpaceID> MetaClient::getSpaceIdByNameFromCache(const std::string& name) {
  auto it = spaceIndexByName_.find(name);
  if (it == spaceIndexByName_.end()) {
    LOG(ERROR) << "Get space id for " << name << " failed";
    return {false, -1};
  }
  return {true, it->second};
}

std::pair<bool, EdgeType> MetaClient::getEdgeTypeByNameFromCache(GraphSpaceID space,
                                                                 const std::string& name) {
  auto it = spaceEdgeIndexByName_.find(std::make_pair(space, name));
  if (it == spaceEdgeIndexByName_.end()) {
    LOG(ERROR) << "getEdgeTypeByNameFromCache(" << space << ", " << name << ") failed";
    return {false, -1};
  }
  return {true, it->second};
}

std::pair<bool, TagID> MetaClient::getTagIdByNameFromCache(GraphSpaceID spaceId,
                                                              const std::string& name) {
  auto it = spaceTagIndexByName_.find(std::make_pair(spaceId, name));
  if (it == spaceTagIndexByName_.end()) {
    LOG(ERROR) << "getTagIdByNameFromCache(" << spaceId << ", " << name << ") failed";
    return {false, -1};
  }
  return {true, it->second};
}

std::pair<bool, std::vector<PartitionID>> MetaClient::getPartsFromCache(GraphSpaceID spaceId) {
  auto iter = spacePartsMap_.find(spaceId);
  if (iter == spacePartsMap_.end()) {
    LOG(ERROR) << "getPartsFromCache(" << spaceId << ") failed";
    return {false, {}};
  }

  return {true, iter->second};
}

std::pair<bool, HostAddr> MetaClient::getPartLeaderFromCache(GraphSpaceID spaceId,
                                                             PartitionID partId) {
  auto iter = spacePartLeaderMap_.find({spaceId, partId});
  if (iter == spacePartLeaderMap_.end()) {
    LOG(ERROR) << "getPartLeaderFromCache(" << spaceId << ", " << partId << ") failed";
    return {false, HostAddr()};
  }

  return {true, iter->second};
}

bool MetaClient::loadData() {
  auto ret = listSpaces();
  if (!ret.first) {
    LOG(ERROR) << "List space failed";
    return false;
  }
  for (auto space : ret.second) {
    GraphSpaceID spaceId = space.first;
    spaceIndexByName_.emplace(space.second, spaceId);
    auto edgesRet = listEdgeSchemas(spaceId);
    if (!edgesRet.first) {
      LOG(ERROR) << "List edge schemas failed";
      return false;
    }
    auto& edgeItems = edgesRet.second;
    for (auto& edgeItem : edgeItems) {
      spaceEdgeIndexByName_[{spaceId, edgeItem.get_edge_name()}] = edgeItem.get_edge_type();
    }

    // tags
    auto tagRet = listTagSchemas(spaceId);
    if (!tagRet.first) {
      LOG(ERROR) << "Get tag schemas failed for spaceId " << spaceId;
      return false;
    }
    auto& tagItems = tagRet.second;
    for (auto& tagItem : tagItems) {
      spaceTagIndexByName_[{spaceId, tagItem.get_tag_name()}] = tagItem.get_tag_id();
    }
  }
  auto hostsRet = listHosts(meta::cpp2::ListHostType::ALLOC);
  if (!hostsRet.first) {
    LOG(ERROR) << "List hosts failed";
    return false;
  }

  auto& hostItems = hostsRet.second;
  LOG(INFO) << "hostItems.size()=" << hostItems.size();
  loadLeader(hostItems, spaceIndexByName_);
  return true;
}

std::pair<bool, std::vector<SpaceIdName>> MetaClient::listSpaces() {
  meta::cpp2::ListSpacesReq req;
  folly::Promise<std::pair<bool, std::vector<SpaceIdName>>> promise;
  auto future = promise.getFuture();
  getResponse(
      std::move(req),
      [](auto client, auto request) { return client->future_listSpaces(request); },
      [this](meta::cpp2::ListSpacesResp&& resp) -> decltype(auto) {
        return std::make_pair(true, this->toSpaceIdName(resp.get_spaces()));
      },
      std::move(promise));
  return std::move(future).get();
}

std::pair<bool, std::vector<meta::cpp2::HostItem>> MetaClient::listHosts(
    meta::cpp2::ListHostType tp) {
  meta::cpp2::ListHostsReq req;
  req.set_type(tp);
  folly::Promise<std::pair<bool, std::vector<meta::cpp2::HostItem>>> promise;
  auto future = promise.getFuture();
  getResponse(
      std::move(req),
      [](auto client, auto request) { return client->future_listHosts(request); },
      [](meta::cpp2::ListHostsResp&& resp) -> decltype(auto) {
        return std::make_pair(true, resp.get_hosts());
      },
      std::move(promise));
  return std::move(future).get();
}

std::pair<bool, std::vector<meta::cpp2::EdgeItem>> MetaClient::listEdgeSchemas(
    GraphSpaceID spaceId) {
  meta::cpp2::ListEdgesReq req;
  req.set_space_id(spaceId);
  folly::Promise<std::pair<bool, std::vector<meta::cpp2::EdgeItem>>> promise;
  auto future = promise.getFuture();
  getResponse(
      std::move(req),
      [](auto client, auto request) { return client->future_listEdges(request); },
      [](meta::cpp2::ListEdgesResp&& resp) -> decltype(auto) {
        return std::make_pair(true, resp.get_edges());
      },
      std::move(promise));
  return std::move(future).get();
}

std::pair<bool, std::vector<meta::cpp2::TagItem>> MetaClient::listTagSchemas(GraphSpaceID spaceId) {
  meta::cpp2::ListTagsReq req;
  req.space_id_ref() = spaceId;
  folly::Promise<std::pair<bool, std::vector<meta::cpp2::TagItem>>> promise;
  auto future = promise.getFuture();
  getResponse(
      std::move(req),
      [](auto client, auto request) { return client->future_listTags(request); },
      [](meta::cpp2::ListTagsResp&& resp) -> decltype(auto) {
        return std::make_pair(true, std::move(resp).get_tags());
      },
      std::move(promise));
  return std::move(future).get();
}

void MetaClient::loadLeader(const std::vector<meta::cpp2::HostItem>& hostItems,
                            const SpaceNameIdMap& spaceIndexByName) {
  for (auto& item : hostItems) {
    for (auto& spaceEntry : item.get_leader_parts()) {
      auto spaceName = spaceEntry.first;
      auto iter = spaceIndexByName.find(spaceName);
      if (iter == spaceIndexByName.end()) {
        continue;
      }
      auto spaceId = iter->second;
      for (const auto& partId : spaceEntry.second) {
        spacePartLeaderMap_[{spaceId, partId}] = item.get_hostAddr();
        spacePartsMap_[spaceId].emplace_back(partId);
      }
    }
  }
}

std::vector<SpaceIdName> MetaClient::toSpaceIdName(
    const std::vector<meta::cpp2::IdName>& tIdNames) {
  std::vector<SpaceIdName> idNames;
  idNames.resize(tIdNames.size());
  std::transform(tIdNames.begin(), tIdNames.end(), idNames.begin(), [](const auto& tin) {
    return SpaceIdName(tin.get_id().get_space_id(), tin.get_name());
  });
  return idNames;
}

template <typename Request,
          typename RemoteFunc,
          typename RespGenerator,
          typename RpcResponse,
          typename Response>
void MetaClient::getResponse(Request req,
                             RemoteFunc remoteFunc,
                             RespGenerator respGen,
                             folly::Promise<std::pair<bool, Response>> pro) {
  auto* evb = DCHECK_NOTNULL(ioExecutor_)->getEventBase();
  HostAddr host = metaAddrs_.back();
  folly::via(evb,
             [host,
              evb,
              req = std::move(req),
              remoteFunc = std::move(remoteFunc),
              respGen = std::move(respGen),
              pro = std::move(pro),
              this]() mutable {
               auto client = clientsMan_->client(host, evb, false, mConfig_.clientTimeoutInMs_);
               LOG(INFO) << "Send request to meta " << host;
               remoteFunc(client, req)
                   .via(evb)
                   .then([host, respGen = std::move(respGen), pro = std::move(pro)](
                             folly::Try<RpcResponse>&& t) mutable {
                     // exception occurred during RPC
                     if (t.hasException()) {
                       LOG(ERROR) << "Send request to meta" << host << " failed";
                       pro.setValue(std::make_pair(false, Response()));
                       return;
                     }
                     auto&& resp = t.value();
                     if (resp.get_code() == nebula::cpp2::ErrorCode::SUCCEEDED) {
                       // succeeded
                       pro.setValue(respGen(std::move(resp)));
                       return;
                     }
                     pro.setValue(std::make_pair(false, Response()));
                   });  // then
             });        // via
}

}  // namespace nebula
