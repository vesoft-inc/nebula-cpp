/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include "common/clients/storage/GraphStorageClient.h"
#include "common/interface/gen-cpp2/storage_types.h"

#include "nebula/sclient/ScanVertexIter.h"

namespace nebula {

ScanVertexIter::ScanVertexIter(const ScanVertexIter& rhs)
    : client_(rhs.client_),
      req_(new storage::cpp2::ScanVertexRequest(*rhs.req_)),
      hasNext_(rhs.hasNext_),
      nextCursor_(rhs.nextCursor_) {}

ScanVertexIter::ScanVertexIter(ScanVertexIter&& rhs) noexcept
    : client_(rhs.client_), hasNext_(rhs.hasNext_), nextCursor_(std::move(rhs.nextCursor_)) {
    req_ = rhs.req_;
    rhs.req_ = nullptr;
}

ScanVertexIter& ScanVertexIter::operator=(const ScanVertexIter& rhs) {
    if (this != &rhs) {
        client_ = rhs.client_;
        delete req_;
        req_ = new storage::cpp2::ScanVertexRequest(*rhs.req_);
        hasNext_ = rhs.hasNext_;
        nextCursor_ = rhs.nextCursor_;
    }

    return *this;
}

ScanVertexIter::~ScanVertexIter() {
    delete req_;
}

DataSet ScanVertexIter::next() {
    DCHECK(hasNext_);
    DCHECK(!!req_);
    req_->set_cursor(std::move(nextCursor_));
    auto r = client_->scanVertex(*req_).get();
    if (!r.ok()) {
        LOG(ERROR) << "Scan vertex failed: " << r.status();
        this->hasNext_ = false;
        return DataSet();
    }
    auto scanResponse = std::move(r).value();
    if (scanResponse.get_result().get_failed_parts().size() != 0) {
        auto errorCode = scanResponse.get_result().get_failed_parts()[0].code;
        LOG(ERROR) << "Scan vertex failed, errorcode: "
                   << static_cast<int32_t>(errorCode);
        this->hasNext_ = false;
        return DataSet();
    }
    this->hasNext_ = scanResponse.get_has_next();
    std::string* cursor = scanResponse.get_next_cursor();
    if (cursor) {
        this->nextCursor_ = *cursor;
    }
    auto data = scanResponse.get_vertex_data();
    return data;
}

}   //  namespace nebula
