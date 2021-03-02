/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <atomic>
#include <chrono>
#include <thread>

#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Init.h>

int main(int argc, char* argv[]) {
    nebula::init(&argc, &argv);

    nebula::ConnectionPool pool;
    pool.init({"127.0.0.1:9669"}, nebula::Config{});
    auto session = pool.getSession("root", "nebula");
    if (!session.valid()) {
        return -1;
    }

    auto result = session.execute("SHOW HOSTS");
    if (result.errorCode() != nebula::ErrorCode::SUCCEEDED) {
        std::cout << "Exit with error code: " << static_cast<int>(result.errorCode()) << std::endl;
        return static_cast<int>(result.errorCode());
    }
    std::cout << *result.data();

    std::atomic_bool complete{false};
    session.asyncExecute("SHOW HOSTS", [&complete](nebula::ResultSet&& cbResult) {
        if (cbResult.errorCode() != nebula::ErrorCode::SUCCEEDED) {
            std::cout << "Exit with error code: " << static_cast<int>(cbResult.errorCode())
                      << std::endl;
            std::exit(static_cast<int>(cbResult.errorCode()));
        }
        std::cout << *cbResult.data();
        complete.store(true);
    });

    while (!complete.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    session.release();
    return 0;
}
