/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <common/Init.h>
#include <nebula/sclient/ScanEdgeIter.h>
#include <nebula/sclient/StorageClient.h>

#include <atomic>
#include <chrono>
#include <limits>
#include <thread>

#include "common/graph/Response.h"

void scanEdge(nebula::StorageClient& c,
              bool auth = false,
              const std::string& username = "",
              const std::string& password = "") {
  auto scanEdgeIter = c.scanEdgeWithPart("nba",
                                         1,
                                         "like",
                                         std::vector<std::string>{"likeness"},
                                         10,
                                         0,
                                         std::numeric_limits<int64_t>::max(),
                                         "",
                                         true,
                                         true,
                                         auth,
                                         username,
                                         password);
  std::cout << "scan edge..." << std::endl;
  while (scanEdgeIter.hasNext()) {
    std::cout << "-------------------------" << std::endl;
    std::pair<nebula::ErrorCode, nebula::DataSet> res = scanEdgeIter.next();
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;
    std::cout << "+++++++++++++++++++++++++" << std::endl;
  }
}

void scanVertex(nebula::StorageClient& c,
                bool auth = false,
                const std::string& username = "",
                const std::string& password = "") {
  nebula::ScanVertexIter scanVertexIter =
      c.scanVertexWithPart("nba",
                           1,
                           {{"player", std::vector<std::string>{"name"}}},
                           10,
                           0,
                           std::numeric_limits<int64_t>::max(),
                           "",
                           true,
                           true,
                           auth,
                           username,
                           password);
  std::cout << "scan vertex..." << std::endl;
  while (scanVertexIter.hasNext()) {
    std::cout << "-------------------------" << std::endl;
    std::pair<nebula::ErrorCode, nebula::DataSet> res = scanVertexIter.next();
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;
    std::cout << "+++++++++++++++++++++++++" << std::endl;
  }
}

int main(int argc, char* argv[]) {
  nebula::init(&argc, &argv);
  nebula::StorageClient c({"127.0.0.1:9559"});

  scanVertex(c);
  scanEdge(c);

  scanVertex(c, true, "root", "nebula");
  scanEdge(c, true, "root", "nebula");

  return 0;
}
