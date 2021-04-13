/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include "common/clients/storage/GraphStorageClient.h"
#include "common/interface/gen-cpp2/storage_types.h"

#include "nebula/sclient/ScanResultIter.h"

namespace nebula {

ScanResultIter::~ScanResultIter() {
    delete req_;
}

ScanResultIter& ScanResultIter::operator=(const ScanResultIter& rhs) {
    if (this != &rhs) {
        client_ = rhs.client_;
        delete req_;
        req_ = new storage::cpp2::ScanEdgeRequest(*rhs.req_);
        hasNext_ = rhs.hasNext_;
        nextCursor_ = rhs.nextCursor_;
    }

    return *this;
}

DataSet ScanResultIter::next() {
    DCHECK(hasNext_);
    DCHECK(!!req_);
    req_->set_cursor(std::move(nextCursor_));
    auto r = client_->scanEdge(*req_).get();
    if (!r.ok()) {
        LOG(ERROR) << "Scan edge failed: " << r.status();
        this->hasNext_ = false;
        return DataSet();
    }
    auto scanEdgeResponse = std::move(r).value();
    if (scanEdgeResponse.get_result().get_failed_parts().size() != 0) {
        auto errorCode = scanEdgeResponse.get_result().get_failed_parts()[0].code;
        LOG(ERROR) << "Scan edge failed, errorcode: "
                   << static_cast<int32_t>(errorCode);
        this->hasNext_ = false;
        return DataSet();
    }
    this->hasNext_ = scanEdgeResponse.get_has_next();
    std::string* cursor = scanEdgeResponse.get_next_cursor();
    if (cursor) {
        this->nextCursor_ = *cursor;
    }
    auto edgeData = scanEdgeResponse.get_edge_data();
    return edgeData;
}

}   //  namespace nebula
