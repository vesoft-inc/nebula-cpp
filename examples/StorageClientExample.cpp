/* Copyright (c) 2021 vesoft inc. All rights reserved.
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

    nebula::StorageClient c({"localhost:9559"});

    auto scanEdgeIter = c.scanEdgeWithPart("nba",
                                           1,
                                           "like",
                                           std::vector<std::string>{"likeness"},
                                           10,
                                           0,
                                           std::numeric_limits<int64_t>::max(),
                                           "",
                                           true,
                                           true);
    std::cout << "scan edge..." << std::endl;
    while (scanEdgeIter.hasNext()) {
        std::cout << "-------------------------" << std::endl;
        nebula::DataSet ds = scanEdgeIter.next();
        std::cout << ds << std::endl;
        std::cout << "+++++++++++++++++++++++++" << std::endl;
    }

    auto scanVertexIter = c.scanVertexWithPart("nba",
                                               1,
                                               "player",
                                               std::vector<std::string>{},
                                               10,
                                               0,
                                               std::numeric_limits<int64_t>::max(),
                                               "",
                                               true,
                                               true);

    std::cout << "scan vertex" << std::endl;
    while (scanVertexIter.hasNext()) {
        std::cout << "-------------------------" << std::endl;
        nebula::DataSet ds = scanVertexIter.next();
        std::cout << ds << std::endl;
        std::cout << "+++++++++++++++++++++++++" << std::endl;
    }

    return 0;
}
