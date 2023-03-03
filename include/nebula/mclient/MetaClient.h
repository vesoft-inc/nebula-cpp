/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "common/datatypes/HostAddr.h"
#include "common/thrift/ThriftTypes.h"
#include "nebula/mclient/MConfig.h"

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

namespace folly {

class IOThreadPoolExecutor;
template <class T>
class Promise;

}  // namespace folly

namespace nebula {

namespace thrift {

template <class ClientType>
class ThriftClientManager;

}  // namespace thrift

namespace meta {
namespace cpp2 {

enum class ListHostType;
class HostItem;
class MetaServiceAsyncClient;
class ListSpacesReq;
class ListSpacesResp;
class IdName;
class EdgeItem;
class TagItem;
class ListEdgesReq;
class ListEdgesResp;

}  // namespace cpp2
}  // namespace meta

using SpaceIdName = std::pair<GraphSpaceID, std::string>;
using SpaceNameIdMap = std::unordered_map<std::string, GraphSpaceID>;
using SpaceEdgeNameTypeMap =
    std::unordered_map<std::pair<GraphSpaceID, std::string>, EdgeType, pair_hash>;

using SpaceTagNameTypeMap =
    std::unordered_map<std::pair<GraphSpaceID, std::string>, TagID, pair_hash>;

class MetaClient {
 public:
  explicit MetaClient(const std::vector<std::string> &metaAddrs,
                      const MConfig &mConfig = MConfig{});

  ~MetaClient();

  std::pair<bool, GraphSpaceID> getSpaceIdByNameFromCache(const std::string &name);

  std::pair<bool, EdgeType> getEdgeTypeByNameFromCache(GraphSpaceID spaceId,
                                                       const std::string &name);

  std::pair<bool, EdgeType> getTagIdByNameFromCache(GraphSpaceID spaceId, const std::string &name);

  std::pair<bool, std::vector<PartitionID>> getPartsFromCache(GraphSpaceID spaceId);

  std::pair<bool, HostAddr> getPartLeaderFromCache(GraphSpaceID spaceId, PartitionID partId);

 private:
  bool loadData();

  std::pair<bool, std::vector<SpaceIdName>> listSpaces();

  std::pair<bool, std::vector<meta::cpp2::HostItem>> listHosts(meta::cpp2::ListHostType tp);

  std::pair<bool, std::vector<meta::cpp2::EdgeItem>> listEdgeSchemas(GraphSpaceID spaceId);

  std::pair<bool, std::vector<meta::cpp2::TagItem>> listTagSchemas(GraphSpaceID spaceId);

  void loadLeader(const std::vector<nebula::meta::cpp2::HostItem> &hostItems,
                  const SpaceNameIdMap &spaceIndexByName);

  std::vector<SpaceIdName> toSpaceIdName(const std::vector<meta::cpp2::IdName> &tIdNames);

  template <class Request,
            class RemoteFunc,
            class RespGenerator,
            class RpcResponse = typename std::result_of<RemoteFunc(
                std::shared_ptr<meta::cpp2::MetaServiceAsyncClient>, Request)>::type::value_type,
            class Response = typename std::result_of<RespGenerator(RpcResponse)>::type>
  void getResponse(Request req,
                   RemoteFunc remoteFunc,
                   RespGenerator respGen,
                   folly::Promise<std::pair<bool, Response>> pro);

 private:
  std::vector<HostAddr> metaAddrs_;
  MConfig mConfig_;
  SpaceNameIdMap spaceIndexByName_;
  SpaceEdgeNameTypeMap spaceEdgeIndexByName_;
  SpaceTagNameTypeMap spaceTagIndexByName_;
  std::unordered_map<std::pair<GraphSpaceID, PartitionID>, HostAddr, pair_hash> spacePartLeaderMap_;
  std::unordered_map<GraphSpaceID, std::vector<PartitionID>> spacePartsMap_;
  std::shared_ptr<folly::IOThreadPoolExecutor> ioExecutor_;
  std::shared_ptr<thrift::ThriftClientManager<meta::cpp2::MetaServiceAsyncClient>> clientsMan_;
};

}  // namespace nebula
