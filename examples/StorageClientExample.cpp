/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <atomic>
#include <chrono>
#include <limits>
#include <thread>

#include <nebula/sclient/ScanEdgeIter.h>
#include <common/Init.h>
#include <nebula/sclient/StorageClient.h>

int main(int argc, char* argv[]) {
    nebula::init(&argc, &argv);

    nebula::StorageClient c({"127.0.0.1:9559"});

    nebula::ScanEdgeIter scanEdgeIter = c.scanEdgeWithPart("nba",
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

    return 0;
}
