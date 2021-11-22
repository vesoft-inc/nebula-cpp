/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <folly/synchronization/Baton.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <nebula/sclient/Init.h>
#include <nebula/sclient/ScanEdgeIter.h>
#include <nebula/sclient/StorageClient.h>

#include "../../ClientTest.h"

// Require a nebula server could access

#define kServerHost "127.0.0.1"

class StorageClientTest : public ClientTest {
 protected:
  static void runGetParts(nebula::StorageClient &c) {
    auto parts = c.getParts("nba");
    LOG(INFO) << "parts id: ";
    for (auto partId : parts) {
      LOG(INFO) << partId << ",";
    }
    EXPECT_GT(parts.size(), 0);
  }

  static void runScanEdgeWithPart(nebula::StorageClient &c) {
    LOG(INFO) << "run with goodScanIter";
    {
      auto goodScanIter = c.scanEdgeWithPart("nba",
                                             1,
                                             "like",
                                             std::vector<std::string>{"likeness"},
                                             10,
                                             0,
                                             std::numeric_limits<int64_t>::max(),
                                             "",
                                             true,
                                             true);
      while (goodScanIter.hasNext()) {
        std::cout << "-------------------------" << std::endl;
        nebula::DataSet expected({"likeness"});
        nebula::DataSet ds = goodScanIter.next();
        std::cout << ds << std::endl;
        // EXPECT_EQ(goodScanIter.hasNext_, false);
        // EXPECT_EQ(goodScanIter.nextCursor_, "");
        // EXPECT_TRUE(verifyResultWithoutOrder(ds, expected));
        std::cout << "+++++++++++++++++++++++++" << std::endl;
      }
    }
    LOG(INFO) << "run with badScanIter";
    {
      auto badScanIter = c.scanEdgeWithPart("nba",
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
        EXPECT_EQ(badScanIter.hasNext(), true);
        nebula::DataSet ds = badScanIter.next();
        EXPECT_EQ(ds, nebula::DataSet());
        EXPECT_EQ(badScanIter.hasNext_, false);
        EXPECT_EQ(badScanIter.nextCursor_, "");
      }
    }
  }
};

TEST_F(StorageClientTest, Basic) {
  nebula::StorageClient c({kServerHost ":45996"});
  LOG(INFO) << "Testing run get parts.";
  runGetParts(c);
  LOG(INFO) << "Testing run scan edge with part.";
  runScanEdgeWithPart(c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  nebula::init(&argc, &argv);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
