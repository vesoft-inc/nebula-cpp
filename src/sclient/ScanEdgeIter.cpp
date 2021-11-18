/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "nebula/sclient/ScanEdgeIter.h"
#include "nebula/sclient/StorageClient.h"

#include "../interface/gen-cpp2/storage_types.h"

namespace nebula {

ScanEdgeIter::ScanEdgeIter(StorageClient* client,
                           storage::cpp2::ScanEdgeRequest* req,
                           bool hasNext)
    : client_(client), req_(req), hasNext_(hasNext) {}

bool ScanEdgeIter::hasNext() { return hasNext_; }

ScanEdgeIter::~ScanEdgeIter() { delete req_; }

DataSet ScanEdgeIter::next() {
  if (!hasNext_) {
    LOG(ERROR) << "hasNext() == false !";
    return DataSet();
  }
  DCHECK(!!req_);
  req_->set_cursor(std::move(nextCursor_));
  auto r = client_->doScanEdge(*req_);
  if (!r.first) {
    LOG(ERROR) << "Scan edge failed";
    this->hasNext_ = false;
    return DataSet();
  }
  auto scanResponse = r.second;
  if (!scanResponse.get_result().get_failed_parts().empty()) {
    auto errorCode = scanResponse.get_result().get_failed_parts()[0].code;
    LOG(ERROR) << "Scan edge failed, errorcode: " << static_cast<int32_t>(errorCode);
    this->hasNext_ = false;
    return DataSet();
  }
  this->hasNext_ = scanResponse.get_has_next();
  std::string* cursor = scanResponse.get_next_cursor();
  if (cursor) {
    this->nextCursor_ = *cursor;
  }
  return scanResponse.get_edge_data();
}

}  //  namespace nebula
