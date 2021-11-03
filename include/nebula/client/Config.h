/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <cstdint>

namespace nebula {

struct Config {
  std::uint32_t timeout_{0};   // in ms
  std::uint32_t idleTime_{0};  // in ms
  std::uint32_t maxConnectionPoolSize_{10};
  std::uint32_t minConnectionPoolSize_{0};
};

}  // namespace nebula
