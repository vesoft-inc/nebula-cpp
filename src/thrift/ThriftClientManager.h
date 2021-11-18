/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/EventBaseManager.h>

#include "common/datatypes/HostAddr.h"

namespace nebula {
namespace thrift {

template <class ClientType>
class ThriftClientManager final {
 public:
  std::shared_ptr<ClientType> client(const HostAddr& host,
                                     folly::EventBase* evb = nullptr,
                                     bool compatibility = false,
                                     uint32_t timeout = 0);

  ~ThriftClientManager() { VLOG(3) << "~ThriftClientManager"; }

  explicit ThriftClientManager(bool enableSSL = false) : enableSSL_(enableSSL) {
    VLOG(3) << "ThriftClientManager";
  }

 private:
  using ClientMap =
      std::unordered_map<std::pair<HostAddr, folly::EventBase*>, std::shared_ptr<ClientType>>;

  folly::ThreadLocal<ClientMap> clientMap_;
  // whether enable ssl
  bool enableSSL_{false};
};

}  // namespace thrift
}  // namespace nebula

#include "../thrift/ThriftClientManager-inl.h"
