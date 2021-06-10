/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <atomic>
#include <chrono>
#include <ctime>
#include <limits>
#include <thread>

#include <nebula/sclient/Init.h>
#include <nebula/sclient/StorageClient.h>

int main(int argc, char* argv[]) {
    nebula::init(&argc, &argv);

    nebula::StorageClient c({nebula::MetaHostAddr("192.168.8.149", 9559)});

    auto partsLeader = c.getPartsLeader("mobile");
    for (auto& p : partsLeader) {
        std::cout << p.first << ":" << p.second << std::endl;
    }
    std::cout << "total parts: " << partsLeader.size() << std::endl;
    std::vector<std::thread> workers;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    for (auto& partLeader : partsLeader) {
        auto partId = partLeader.first;
        workers.emplace_back(std::thread([&c, partId] {
            // auto partStart = std::clock();
            auto scanVertexIter = c.scanVertexWithPart("mobile",
                                                       partId,
                                                       "mobile_vertex",
                                                       std::vector<std::string>{"_vid"},
                                                       10000,
                                                       0,
                                                       std::numeric_limits<int64_t>::max(),
                                                       "",
                                                       true,
                                                       true);
            auto partSize = 0;
            while (scanVertexIter.hasNext()) {
                nebula::DataSet ds = scanVertexIter.next();
                partSize += ds.size();
            }
            // auto partEnd = std::clock();
            // std::cout << "part: " << partId << ", size: " << partSize << " cost: " <<
            // (double)(partEnd - partStart) / CLOCKS_PER_SEC << std::endl;
        }));
    }
    for (auto& worker : workers) {
        worker.join();
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;

    return 0;
}
