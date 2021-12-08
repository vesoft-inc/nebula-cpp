/* Copyright (c) 2021 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <thrift/lib/cpp2/GeneratedCodeHelper.h>
#include <thrift/lib/cpp2/gen/module_types_tcc.h>
#include <thrift/lib/cpp2/protocol/ProtocolReaderStructReadState.h>

#include <memory>

#include "common/graph/GraphCpp2Ops.h"
#include "common/graph/Response.h"
#include "common/utils/utils.h"

namespace apache {
namespace thrift {

/**************************************
 *
 * Ops for class VerifyClientVersionReq
 *
 *************************************/
namespace detail {

template <>
struct TccStructTraits<nebula::VerifyClientVersionReq> {
  static void translateFieldName(MAYBE_UNUSED folly::StringPiece _fname,
                                 MAYBE_UNUSED int16_t& fid,
                                 MAYBE_UNUSED apache::thrift::protocol::TType& _ftype) {
    if (false) {
    } else if (_fname == "version") {
      fid = 1;
      _ftype = apache::thrift::protocol::T_STRING;
    }
  }
};

}  // namespace detail

inline constexpr apache::thrift::protocol::TType
Cpp2Ops<::nebula::VerifyClientVersionReq>::thriftType() {
  return apache::thrift::protocol::T_STRUCT;
}

template <class Protocol>
uint32_t Cpp2Ops<::nebula::VerifyClientVersionReq>::write(
    Protocol* proto, ::nebula::VerifyClientVersionReq const* obj) {
  uint32_t xfer = 0;
  xfer += proto->writeStructBegin("nebula::VerifyClientVersionReq");
  xfer += proto->writeFieldBegin("version", apache::thrift::protocol::T_STRING, 1);
  xfer += proto->writeBinary(obj->version);
  xfer += proto->writeFieldEnd();
  xfer += proto->writeFieldStop();
  xfer += proto->writeStructEnd();
  return xfer;
}

template <class Protocol>
void Cpp2Ops<::nebula::VerifyClientVersionReq>::read(Protocol* proto,
                                                     ::nebula::VerifyClientVersionReq* obj) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol> _readState;

  _readState.readStructBegin(proto);

  using apache::thrift::TProtocolException;

  bool isset_version = false;

  if (UNLIKELY(!_readState.advanceToNextField(proto, 0, 1, apache::thrift::protocol::T_STRING))) {
    goto _loop;
  }
_readField_version : {
  proto->readBinary(obj->version);
  isset_version = true;
}

_end:
  _readState.readStructEnd(proto);

  if (!isset_version) {
    TProtocolException::throwMissingRequiredField("version", "nebula::VerifyClientVersionReq");
  }
  return;

_loop:
  if (_readState.fieldType == apache::thrift::protocol::T_STOP) {
    goto _end;
  }
  if (proto->kUsesFieldNames()) {
    apache::thrift::detail::TccStructTraits<nebula::VerifyClientVersionReq>::translateFieldName(
        _readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1: {
      if (LIKELY(_readState.fieldType == apache::thrift::protocol::T_STRING)) {
        goto _readField_version;
      } else {
        goto _skip;
      }
    }
    default: {
_skip:
      proto->skip(_readState.fieldType);
      _readState.readFieldEnd(proto);
      _readState.readFieldBeginNoInline(proto);
      goto _loop;
    }
  }
}

template <class Protocol>
uint32_t Cpp2Ops<::nebula::VerifyClientVersionReq>::serializedSize(
    Protocol const* proto, ::nebula::VerifyClientVersionReq const* obj) {
  uint32_t xfer = 0;
  xfer += proto->serializedStructSize("nebula::VerifyClientVersionReq");
  xfer += proto->serializedFieldSize("version", apache::thrift::protocol::T_STRING, 1);
  xfer += proto->serializedSizeBinary(obj->version);
  xfer += proto->serializedSizeStop();
  return xfer;
}

template <class Protocol>
uint32_t Cpp2Ops<::nebula::VerifyClientVersionReq>::serializedSizeZC(
    Protocol const* proto, ::nebula::VerifyClientVersionReq const* obj) {
  uint32_t xfer = 0;
  xfer += proto->serializedStructSize("nebula::VerifyClientVersionReq");
  xfer += proto->serializedFieldSize("version", apache::thrift::protocol::T_STRING, 1);
  xfer += proto->serializedSizeZCBinary(obj->version);
  xfer += proto->serializedSizeStop();
  return xfer;
}

}  // namespace thrift
}  // namespace apache
