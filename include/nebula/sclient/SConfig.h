/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <cstdint>
#include <string>

namespace nebula {

struct SConfig {
  // It's as same as FLAGS_conn_timeout_ms in nebula
  int32_t connTimeoutInMs_{1000};
  // It's as same as FLAG_meta_client_timeout_ms in nebula
  int32_t clientTimeoutInMs_{60 * 1000};
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
