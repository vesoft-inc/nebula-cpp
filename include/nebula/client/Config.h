/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <cstdint>
#include <string>

namespace nebula {

struct Config {
  std::uint32_t timeout_{0};   // in ms
  std::uint32_t idleTime_{0};  // in ms
  std::uint32_t maxConnectionPoolSize_{10};
  std::uint32_t minConnectionPoolSize_{0};
  // Whether to enable SSL encryption
  bool enableSSL_{false};
  // Whether to enable mTLS
  bool enableMTLS_{false};
  // Whether to check peer CN or SAN
  bool checkPeerName_{false};
  std::string peerName_;
  // Path to cert of CA
  std::string CAPath_;
  // Path to cert of client
  std::string certPath_;
  // path to private key of client
  std::string keyPath_;
};

}  // namespace nebula
