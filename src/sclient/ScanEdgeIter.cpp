/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "nebula/sclient/ScanEdgeIter.h"

#include "../interface/gen-cpp2/storage_types.h"
#include "nebula/sclient/StorageClient.h"

namespace nebula {

ScanEdgeIter::ScanEdgeIter(StorageClient* client, storage::cpp2::ScanEdgeRequest* req, bool hasNext)
    : client_(client), req_(req), hasNext_(hasNext) {}

bool ScanEdgeIter::hasNext() { return hasNext_; }

ScanEdgeIter::~ScanEdgeIter() { delete req_; }

DataSet ScanEdgeIter::next() {
  if (!hasNext()) {
    LOG(ERROR) << "hasNext() == false !";
    return DataSet();
  }
  DCHECK(!!req_);
  if (firstScan_) {
    firstScan_ = false;
  } else {
    auto partCursorMapReq = req_->get_parts();
    DCHECK_EQ(partCursorMapReq.size(), 1);
    partCursorMapReq.begin()->second.set_has_next(true);
    partCursorMapReq.begin()->second.set_next_cursor(nextCursor_);
    LOG(INFO) << "nextCursor of req: " << partCursorMapReq.begin()->second.get_next_cursor();
    req_->set_parts(partCursorMapReq);
  }
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
  auto partCursorMapResp = scanResponse.get_cursors();
  DCHECK_EQ(partCursorMapResp.size(), 1);
  auto scanCursor = partCursorMapResp.begin()->second;
  hasNext_ = scanCursor.get_has_next();
  LOG(INFO) << "hasNext: " << hasNext_;
  if (hasNext_) {
    nextCursor_ = *scanCursor.get_next_cursor();
    LOG(INFO) << "nextCursor: " << nextCursor_;
  }

  return scanResponse.get_edge_data();
}

}  //  namespace nebula
