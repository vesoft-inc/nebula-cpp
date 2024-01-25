/* Copyright (c) 2023 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "nebula/sclient/ScanVertexIter.h"

#include "../interface/gen-cpp2/storage_types.h"
#include "nebula/sclient/StorageClient.h"

namespace nebula {

ScanVertexIter::ScanVertexIter(StorageClient* client,
                               storage::cpp2::ScanVertexRequest* req,
                               bool hasNext)
    : client_(client), req_(req), hasNext_(hasNext) {}

bool ScanVertexIter::hasNext() {
  return hasNext_;
}

ScanVertexIter::~ScanVertexIter() {
  delete req_;
}

std::pair<::nebula::ErrorCode, DataSet> ScanVertexIter::next() {
  DCHECK(hasNext()) << "hasNext() == false !";
  DCHECK(!!req_);
  auto partCursorMapReq = req_->get_parts();
  DCHECK_EQ(partCursorMapReq.size(), 1);
  partCursorMapReq.begin()->second.set_next_cursor(nextCursor_);
  req_->set_parts(partCursorMapReq);
  auto r = client_->doScanVertex(*req_);
  auto code = r.first;
  if (code != ::nebula::ErrorCode::SUCCEEDED) {
    LOG(ERROR) << "Scan vertex failed, error code: " << static_cast<int32_t>(code);
    this->hasNext_ = false;
    return {code, DataSet()};
  }
  auto scanResponse = r.second;
  DCHECK(scanResponse.get_result().get_failed_parts().empty());
  auto partCursorMapResp = scanResponse.get_cursors();
  DCHECK_EQ(partCursorMapResp.size(), 1);
  auto scanCursor = partCursorMapResp.begin()->second;
  hasNext_ = scanCursor.next_cursor_ref().has_value();
  if (hasNext_) {
    nextCursor_ = scanCursor.next_cursor_ref().value();
  }

  return {::nebula::ErrorCode::SUCCEEDED, *scanResponse.get_props()};
}

}  //  namespace nebula
