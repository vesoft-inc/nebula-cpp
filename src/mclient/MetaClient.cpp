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

MetaClient::MetaClient(const std::vector<std::string>& metaAddrs) {
  for (const auto& addr : metaAddrs) {
    std::vector<std::string> ip_port;
    folly::split(':', addr, ip_port, true);
    CHECK(ip_port.size() == 2) << "meta server addr " << addr << " is illegal";
    metaAddrs_.emplace_back(ip_port[0], folly::to<int32_t>(ip_port[1]));
  }
  CHECK(!metaAddrs_.empty()) << "metaAddrs_ is empty";

  ioExecutor_ = std::make_shared<folly::IOThreadPoolExecutor>(std::thread::hardware_concurrency());
  clientsMan_ =
      std::make_shared<thrift::ThriftClientManager<meta::cpp2::MetaServiceAsyncClient>>(false);
  bool b = loadData();  // load data into cache
  if (!b) {
    LOG(INFO) << "load data failed";
  } else {
    LOG(INFO) << "load data succecced";
    LOG(INFO) << spaceIndexByName_.size();
    LOG(INFO) << spaceEdgeIndexByName_.size();
    LOG(INFO) << spacePartLeaderMap_.size();
    LOG(INFO) << spacePartsMap_.size();
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
    LOG(ERROR) << "Get edge type for " << name << " failed";
    return {false, -1};
  }
  return {true, it->second};
}

std::pair<bool, std::vector<PartitionID>> MetaClient::getPartsFromCache(GraphSpaceID spaceId) {
  LOG(INFO) << "getPartsFromCache(" << spaceId << ")";
  for (auto kv : spacePartsMap_) {
    LOG(INFO) << kv.first << ", ";
    for (auto partId : kv.second) {
      LOG(INFO) << partId;
    }
  }
  auto iter = spacePartsMap_.find(spaceId);
  if (iter == spacePartsMap_.end()) {
    return {false, {}};
  }

  return {true, iter->second};
}

std::pair<bool, HostAddr> MetaClient::getPartLeaderFromCache(GraphSpaceID spaceId,
                                                             PartitionID partId) {
  auto iter = spacePartLeaderMap_.find({spaceId, partId});
  if (iter == spacePartLeaderMap_.end()) {
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

void MetaClient::loadLeader(const std::vector<meta::cpp2::HostItem>& hostItems,
                            const SpaceNameIdMap& spaceIndexByName) {
  LOG(INFO) << "loadLeader start";
  for (auto& item : hostItems) {
    LOG(INFO) << "item.get_leader_parts().size()=" << item.get_leader_parts().size();
    LOG(INFO) << "item.get_all_parts().size()=" << item.get_all_parts().size();
    for (auto& spaceEntry : item.get_leader_parts()) {
      auto spaceName = spaceEntry.first;
      LOG(INFO) << "[" << spaceName << "]";
      auto iter = spaceIndexByName.find(spaceName);
      if (iter == spaceIndexByName.end()) {
        LOG(INFO) << "dont' find " << spaceName;
        continue;
      }
      auto spaceId = iter->second;
      LOG(INFO) << "spaceId:" << spaceId;
      LOG(INFO) << "spaceEntry.second.size()" << spaceEntry.second.size();
      for (const auto& partId : spaceEntry.second) {
        LOG(INFO) << "spaceId: " << spaceId << ", partId: " << partId
                  << ", host: " << item.get_hostAddr();
        spacePartLeaderMap_[{spaceId, partId}] = item.get_hostAddr();
        spacePartsMap_[spaceId].emplace_back(partId);
      }
    }
  }
  LOG(INFO) << "loadLeader end";
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
               auto client = clientsMan_->client(
                   host, evb, false, 60 * 1000);  // FLAGS_meta_client_timeout_ms
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
