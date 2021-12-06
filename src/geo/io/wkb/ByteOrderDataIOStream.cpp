/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "common/geo/io/wkb/ByteOrderDataIOStream.h"

#include <glog/logging.h>

#include <boost/endian/conversion.hpp>

namespace nebula {
namespace geo {

struct ByteOrderData {
  static ByteOrder getMachineByteOrder() {
    static int endianCheck = 1;
    return static_cast<ByteOrder>(
        *(reinterpret_cast<char *>(&endianCheck)));  // 0 for BigEndian, 1 for LittleEndian
  }

  static void putUint32(uint8_t *buf, ByteOrder byteOrder, uint32_t v) {
    if (byteOrder == ByteOrder::BigEndian) {
      boost::endian::store_big_u32(buf, v);
    } else {
      DCHECK(byteOrder == ByteOrder::LittleEndian);
      boost::endian::store_little_u32(buf, v);
    }
  }

  static void putUint64(uint8_t *buf, ByteOrder byteOrder, uint64_t v) {
    if (byteOrder == ByteOrder::BigEndian) {
      boost::endian::store_big_u64(buf, v);
    } else {
      DCHECK(byteOrder == ByteOrder::LittleEndian);
      boost::endian::store_little_u64(buf, v);
    }
  }

  static void putDouble(uint8_t *buf, ByteOrder byteOrder, double v) {
    const char *c = reinterpret_cast<const char *>(&v);
    uint64_t v2 = *reinterpret_cast<const uint64_t *>(c);
    putUint64(buf, byteOrder, v2);
  }
};

void ByteOrderDataOutStream::writeUint8(uint8_t v) {
  buf_[0] = v;
  stream_.write(reinterpret_cast<char *>(buf_), 1);
}

void ByteOrderDataOutStream::writeUint32(uint32_t v) {
  ByteOrderData::putUint32(buf_, byteOrder_, v);
  stream_.write(reinterpret_cast<char *>(buf_), 4);
}

void ByteOrderDataOutStream::writeDouble(double v) {
  ByteOrderData::putDouble(buf_, byteOrder_, v);
  stream_.write(reinterpret_cast<char *>(buf_), 8);
}

}  // namespace geo
}  // namespace nebula
