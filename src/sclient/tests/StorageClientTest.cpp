/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

#include <nebula/sclient/Init.h>
#include <nebula/sclient/ScanEdgeIter.h>
#include <nebula/sclient/StorageClient.h>
#include "./ClientTest.h"

// Require a nebula server could access

static constexpr char kServerHost[] = "127.0.0.1";

class StorageClientTest : public ClientTest {
protected:
    static void runGetPartsAlloc(nebula::StorageClient &c) {
        std::cout << "get parts alloc of space" << std::endl;
        auto partsAlloc = c.getPartsAlloc("nba");
        for (auto p : partsAlloc) {
            std::cout << "partReplicaSize[" << p.first << "]=" << p.second.size() << std::endl;
        }
        std::cout << "-----------------------" << std::endl;
    }

    static void runGetPartsLeader(nebula::StorageClient &c) {
        std::cout << "get parts leader of space" << std::endl;
        auto partsLeader = c.getPartsLeader("nba");
        for (auto p : partsLeader) {
            std::cout << "partLeader[" << p.first << "]=" << p.second << std::endl;
        }
        std::cout << "-----------------------" << std::endl;
    }

    static void runScanEdge(nebula::StorageClient &c) {
        auto scanResultIter = c.scanEdgeWithPart("nba",
                                                 999,
                                                 "like",
                                                 std::vector<std::string>(),
                                                 1000,
                                                 0,
                                                 std::numeric_limits<int64_t>::max(),
                                                 "",
                                                 true,
                                                 true);
        {
            EXPECT_EQ(scanResultIter.hasNext(), true);
            nebula::DataSet ds = scanResultIter.next();
            EXPECT_EQ(ds, nebula::DataSet());
            EXPECT_EQ(scanResultIter.hasNext_, false);
            EXPECT_EQ(scanResultIter.nextCursor_, "");
        }

        scanResultIter = c.scanEdgeWithPart("nba",
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
            // EXPECT_EQ(scanResultIter.hasNext_, false);
            // EXPECT_EQ(scanResultIter.nextCursor_, "");
            // EXPECT_TRUE(verifyResultWithoutOrder(ds, expected));
            std::cout << "+++++++++++++++++++++++++" << std::endl;
        }
    }

    static void runScanVertex(nebula::StorageClient &c) {
        auto scanResultIter = c.scanVertexWithPart("nba",
                                                   999,
                                                   "non_exist_tag",
                                                   std::vector<std::string>(),
                                                   1000,
                                                   0,
                                                   std::numeric_limits<int64_t>::max(),
                                                   "",
                                                   true,
                                                   true);
        {
            EXPECT_EQ(scanResultIter.hasNext(), false);
            // nebula::DataSet ds = scanResultIter.next();
            // EXPECT_EQ(ds, nebula::DataSet());
            EXPECT_EQ(scanResultIter.hasNext_, false);
            EXPECT_EQ(scanResultIter.nextCursor_, "");
        }

        scanResultIter = c.scanVertexWithPart("nba",
                                              1,
                                              "player",
                                              std::vector<std::string>{"name", "age"},
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
            // EXPECT_EQ(scanResultIter.hasNext_, false);
            // EXPECT_EQ(scanResultIter.nextCursor_, "");
            // EXPECT_TRUE(verifyResultWithoutOrder(ds, expected));
            std::cout << "+++++++++++++++++++++++++" << std::endl;
        }
    }
};

TEST_F(StorageClientTest, ScanEdge) {
    nebula::StorageClient c({nebula::MetaHostAddr("localhost", 45996)});
    LOG(INFO) << "Testing run get parts alloc.";
    runGetPartsAlloc(c);
    LOG(INFO) << "Testing run get parts leader.";
    runGetPartsLeader(c);
    LOG(INFO) << "Testing run scan edge.";
    runScanEdge(c);
    LOG(INFO) << "Testing run scan vertex.";
    runScanVertex(c);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    nebula::init(&argc, &argv);
    google::SetStderrLogging(google::INFO);

    return RUN_ALL_TESTS();
}
