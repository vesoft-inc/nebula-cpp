/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "./SSLConfig.h"

#include <folly/io/async/SSLOptions.h>

namespace nebula {

std::shared_ptr<folly::SSLContext> createSSLContext(const SSLConfig &cfg) {
    if (cfg.check_peer_name && cfg.peer_name.empty()) {
        throw std::runtime_error("peer name checking enabled but not provied");
    }

    if (cfg.enable_mtls && (cfg.cert_path.empty() || cfg.key_path.empty())) {
        throw std::runtime_error("mTLS enabled but cert/key not provided");
    }

    auto context = std::make_shared<folly::SSLContext>();

    if (!cfg.ca_path.empty()) {
        context->loadTrustedCertificates(cfg.ca_path.c_str());
        if (cfg.check_peer_name) {
            context->authenticate(true, true, cfg.peer_name);
        } else {
            context->authenticate(true, false);
        }
        context->setVerificationOption(folly::SSLContext::SSLVerifyPeerEnum::VERIFY);
    }

    if (cfg.enable_mtls) {
        context->loadCertKeyPairFromFiles(cfg.cert_path.c_str(), cfg.key_path.c_str());
    }

    folly::ssl::setSignatureAlgorithms<folly::ssl::SSLCommonOptions>(*context);

    return context;
}

}  // namespace nebula
