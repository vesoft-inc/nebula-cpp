/* Copyright (c) 2023 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <string>
#include <vector>

#include "common/datatypes/DataSet.h"

namespace nebula {
class StorageClient;

namespace storage {
namespace cpp2 {
class ScanVertexRequest;
}  // namespace cpp2
}  // namespace storage

struct ScanVertexIter {
  ScanVertexIter(StorageClient* client, storage::cpp2::ScanVertexRequest* req, bool hasNext = true);

  ~ScanVertexIter();

  bool hasNext();

  DataSet next();

  StorageClient* client_;
  storage::cpp2::ScanVertexRequest* req_;
  bool hasNext_;
  std::string nextCursor_;
};

}  // namespace nebula
