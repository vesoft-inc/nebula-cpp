/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/EventBaseManager.h>

#include "common/datatypes/HostAddr.h"
#include "../SSLConfig.h"

namespace nebula {
namespace thrift {

template <class ClientType>
class ThriftClientManager final {
 public:
  std::shared_ptr<ClientType> client(const HostAddr& host,
                                     folly::EventBase* evb = nullptr,
                                     bool compatibility = false,
                                     uint32_t timeout = 0);

  ~ThriftClientManager() {
    VLOG(3) << "~ThriftClientManager";
  }

  explicit ThriftClientManager(int32_t connTimeoutInMs, bool enableSSL, SSLConfig cfg = SSLConfig())
      : connTimeoutInMs_(connTimeoutInMs), enableSSL_(enableSSL), sslcfg_(std::move(cfg)) {
    VLOG(3) << "ThriftClientManager";
  }

 private:
  using ClientMap =
      std::unordered_map<std::pair<HostAddr, folly::EventBase*>, std::shared_ptr<ClientType>>;

  folly::ThreadLocal<ClientMap> clientMap_;
  int32_t connTimeoutInMs_;
  // whether enable ssl
  bool enableSSL_;
  SSLConfig sslcfg_;
};

}  // namespace thrift
}  // namespace nebula

#include "../thrift/ThriftClientManager-inl.h"
