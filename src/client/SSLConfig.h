/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include <folly/io/async/SSLContext.h>

namespace nebula {

std::shared_ptr<folly::SSLContext> createSSLContext(const std::string &CAPath);

}  // namespace nebula
