/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <cstdint>
#include <string>

namespace nebula {

struct SConfig {
  int32_t connTimeoutInMs_{1000};  // in ms. It's as same as FLAGS_conn_timeout_ms in nebula
  int32_t clientTimeoutInMs_{60 *
                             1000};  // in ms. It's as same as FLAG_meta_client_timeout_ms in nebula
  bool enableSSL_{false};
  std::string CAPath_;
};

}  // namespace nebula
