/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <folly/io/async/SSLContext.h>

namespace nebula {

struct SSLConfig final {
    // Whether to enable mTLS(mutual TLS authentication)
    bool enable_mtls{false};
    // Check whether the given peername matches the CN or SAN in the certificate
    bool check_peer_name{false};
    std::string peer_name;
    // Path to certificate(s) of the CA used to authenticate the cert of server
    std::string ca_path;
    // Path to the client cert, must be present if mTLS enabled
    std::string cert_path;
    // Path to the client private key, must be present if mTLS enabled
    std::string key_path;
};

std::shared_ptr<folly::SSLContext> createSSLContext(const SSLConfig &cfg);

}  // namespace nebula
