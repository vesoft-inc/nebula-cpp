// Copyright (c) 2022 vesoft inc. All rights reserved.
//
// This source code is licensed under Apache 2.0 License.

#include <common/Init.h>
#include <nebula/client/SessionPool.h>

#include <atomic>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
  nebula::init(&argc, &argv);
  {
    // Create space
    nebula::ConnectionPool pool;
    pool.init({"127.0.0.1:9669"}, nebula::Config{0, 0, 1, 0, "", false});
    auto session = pool.getSession("root", "nebula");
    assert(session.valid());

    auto resp = session.execute(
        "CREATE SPACE IF NOT EXISTS session_pool_test(vid_type = FIXED_STRING(16));");
    assert(resp.errorCode == nebula::ErrorCode::SUCCEEDED);
  }

  nebula::SessionPoolConfig config;
  config.username_ = "root";
  config.password_ = "nebula";
  config.addrs_ = {"127.0.0.1:9669"};
  config.spaceName_ = "session_pool_test";
  config.maxSize_ = 10;
  nebula::SessionPool pool(config);
  pool.init();

  std::vector<std::thread> threads;
  for (std::size_t i = 0; i < config.maxSize_; ++i) {
    threads.emplace_back([&pool]() {
      auto resp = pool.execute("YIELD 1");
      assert(resp.errorCode == nebula::ErrorCode::SUCCEEDED);
      std::cout << "Result: " << *resp.data << std::endl;
    });
  }
  for (auto& t : threads) {
    t.join();
  }
}
