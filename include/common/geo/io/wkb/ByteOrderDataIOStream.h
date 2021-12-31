/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <sstream>

#include "common/geo/io/wkb/ByteOrder.h"

namespace nebula {
namespace geo {

class ByteOrderDataOutStream {
 public:
  ByteOrderDataOutStream() = default;

  ~ByteOrderDataOutStream() = default;

  std::string str() const {
    return stream_.str();
  }

  void setByteOrder(ByteOrder order) {
    byteOrder_ = order;
  }

  void writeUint8(uint8_t v);

  void writeUint32(uint32_t v);

  void writeDouble(double v);

 private:
  ByteOrder byteOrder_;
  std::ostringstream stream_;
  unsigned char buf_[8];
};

}  // namespace geo
}  // namespace nebula
