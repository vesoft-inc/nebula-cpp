/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <atomic>
#include <chrono>
#include <limits>
#include <thread>

#include <nebula/sclient/Init.h>
#include <nebula/sclient/StorageClient.h>

int main(int argc, char* argv[]) {
    nebula::init(&argc, &argv);

    nebula::StorageClient c({nebula::MetaHostAddr("localhost", 45996)});

    auto scanResultIter = c.scanEdgeWithPart("nba",
                                             1,
                                             "like",
                                             std::vector<std::string>{"likeness"},
                                             10,
                                             0,
                                             std::numeric_limits<int64_t>::max(),
                                             "",
                                             true,
                                             true);
    while (scanResultIter.hasNext()) {
        std::cout << "-------------------------" << std::endl;
        nebula::DataSet expected({"likeness"});
        nebula::DataSet ds = scanResultIter.next();
        std::cout << ds << std::endl;
        std::cout << "+++++++++++++++++++++++++" << std::endl;
    }

    return 0;
}
