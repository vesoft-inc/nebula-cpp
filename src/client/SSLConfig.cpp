/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "./SSLConfig.h"

#include <folly/io/async/SSLOptions.h>

namespace nebula {

std::shared_ptr<folly::SSLContext> createSSLContext(const std::string &CAPath) {
  auto context = std::make_shared<folly::SSLContext>();
  if (!CAPath.empty()) {
    context->loadTrustedCertificates(CAPath.c_str());
    // don't do peer name validation
    context->authenticate(true, false);
    // verify the server cert
    context->setVerificationOption(folly::SSLContext::SSLVerifyPeerEnum::VERIFY);
  }
  folly::ssl::setSignatureAlgorithms<folly::ssl::SSLCommonOptions>(*context);
  return context;
}

}  // namespace nebula
