/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "common/datatypes/Duration.h"

#include <folly/Format.h>
#include <folly/String.h>
#include <folly/hash/Hash.h>

#include <sstream>

namespace nebula {

std::string Duration::toString() const {
  return folly::format(
             "P{}MT{}.{:0>6}000S", months, seconds + microseconds / 1000000, microseconds % 1000000)
      .str();
}

}  // namespace nebula

namespace std {

// Inject a customized hash function
std::size_t hash<nebula::Duration>::operator()(const nebula::Duration& d) const noexcept {
  size_t hv = folly::hash::fnv64_buf(reinterpret_cast<const void*>(&d.months), sizeof(d.months));
  hv = folly::hash::fnv64_buf(reinterpret_cast<const void*>(d.seconds), sizeof(d.seconds), hv);
  return folly::hash::fnv64_buf(
      reinterpret_cast<const void*>(d.microseconds), sizeof(d.microseconds), hv);
}

}  // namespace std
