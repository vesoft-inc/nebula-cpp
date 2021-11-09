/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
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
  std::string CAPath_;
  bool enableSSL_{false};
};

}  // namespace nebula
