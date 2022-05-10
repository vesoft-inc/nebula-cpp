/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/Init.h>
#include <folly/Format.h>
#include <glog/logging.h>
#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Session.h>

#include <atomic>
#include <chrono>
#include <thread>

// Require a nebula server could access

DEFINE_string(host, "", "Register host address.");
DEFINE_string(server, "127.0.0.1:9669", "Nebula server address.");
DEFINE_bool(enable_ssl, false, "Enable SSL.");

int main(int argc, char** argv) {
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  nebula::ConnectionPool pool;
  nebula::Config c{10, 0, 300, 0, "", FLAGS_enable_ssl};
  pool.init({FLAGS_server}, c);
  auto session = pool.getSession("root", "nebula");
  CHECK(session.valid());

  auto resp =
      session.execute(folly::format("ADD HOSTS {}", FLAGS_host).str());
  CHECK_EQ(resp.errorCode, nebula::ErrorCode::SUCCEEDED) << *resp.errorMsg;
  return 0;
}
