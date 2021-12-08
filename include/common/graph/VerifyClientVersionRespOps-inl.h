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
 * Ops for class VerifyClientVersionResp
 *
 *************************************/
namespace detail {

template <>
struct TccStructTraits<nebula::VerifyClientVersionResp> {
  static void translateFieldName(MAYBE_UNUSED folly::StringPiece _fname,
                                 MAYBE_UNUSED int16_t& fid,
                                 MAYBE_UNUSED apache::thrift::protocol::TType& _ftype) {
    if (false) {
    } else if (_fname == "error_code") {
      fid = 1;
      _ftype = apache::thrift::protocol::T_I32;
    } else if (_fname == "error_msg") {
      fid = 2;
      _ftype = apache::thrift::protocol::T_STRING;
    }
  }
};

}  // namespace detail

inline constexpr apache::thrift::protocol::TType
Cpp2Ops<::nebula::VerifyClientVersionResp>::thriftType() {
  return apache::thrift::protocol::T_STRUCT;
}

template <class Protocol>
uint32_t Cpp2Ops<::nebula::VerifyClientVersionResp>::write(
    Protocol* proto, ::nebula::VerifyClientVersionResp const* obj) {
  uint32_t xfer = 0;
  xfer += proto->writeStructBegin("nebula::VerifyClientVersionResp");
  xfer += proto->writeFieldBegin("error_code", apache::thrift::protocol::T_I32, 1);
  xfer +=
      ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration,
                                                     ::nebula::ErrorCode>::write(*proto,
                                                                                 obj->errorCode);
  xfer += proto->writeFieldEnd();
  if (obj->errorMsg != nullptr) {
    xfer += proto->writeFieldBegin("error_msg", apache::thrift::protocol::T_STRING, 2);
    xfer += proto->writeBinary(*obj->errorMsg);
    xfer += proto->writeFieldEnd();
  }
  xfer += proto->writeFieldStop();
  xfer += proto->writeStructEnd();
  return xfer;
}

template <class Protocol>
void Cpp2Ops<::nebula::VerifyClientVersionResp>::read(Protocol* proto,
                                                      ::nebula::VerifyClientVersionResp* obj) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol> _readState;

  _readState.readStructBegin(proto);

  using apache::thrift::TProtocolException;

  bool isset_error_code = false;

  if (UNLIKELY(!_readState.advanceToNextField(proto, 0, 1, apache::thrift::protocol::T_I32))) {
    goto _loop;
  }
_readField_error_code : {
  ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration,
                                                 ::nebula::ErrorCode>::read(*proto, obj->errorCode);
  isset_error_code = true;
}

  if (UNLIKELY(!_readState.advanceToNextField(proto, 1, 2, apache::thrift::protocol::T_STRING))) {
    goto _loop;
  }
_readField_error_msg : {
  obj->errorMsg = std::make_unique<std::string>();
  proto->readBinary(*obj->errorMsg);
  //    this->__isset.error_msg = true;
}

_end:
  _readState.readStructEnd(proto);

  if (!isset_error_code) {
    TProtocolException::throwMissingRequiredField("error_code", "nebula::VerifyClientVersionResp");
  }
  return;

_loop:
  if (_readState.fieldType == apache::thrift::protocol::T_STOP) {
    goto _end;
  }
  if (proto->kUsesFieldNames()) {
    apache::thrift::detail::TccStructTraits<nebula::VerifyClientVersionResp>::translateFieldName(
        _readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1: {
      if (LIKELY(_readState.fieldType == apache::thrift::protocol::T_I32)) {
        goto _readField_error_code;
      } else {
        goto _skip;
      }
    }
    case 2: {
      if (LIKELY(_readState.fieldType == apache::thrift::protocol::T_STRING)) {
        goto _readField_error_msg;
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
uint32_t Cpp2Ops<::nebula::VerifyClientVersionResp>::serializedSize(
    Protocol const* proto, ::nebula::VerifyClientVersionResp const* obj) {
  uint32_t xfer = 0;
  xfer += proto->serializedStructSize("nebula::VerifyClientVersionResp");
  xfer += proto->serializedFieldSize("error_code", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods<
      ::apache::thrift::type_class::enumeration,
      ::nebula::ErrorCode>::serializedSize<false>(*proto, obj->errorCode);
  if (obj->errorMsg != nullptr) {
    xfer += proto->serializedFieldSize("error_msg", apache::thrift::protocol::T_STRING, 2);
    xfer += proto->serializedSizeBinary(*obj->errorMsg);
  }
  xfer += proto->serializedSizeStop();
  return xfer;
}

template <class Protocol>
uint32_t Cpp2Ops<::nebula::VerifyClientVersionResp>::serializedSizeZC(
    Protocol const* proto, ::nebula::VerifyClientVersionResp const* obj) {
  uint32_t xfer = 0;
  xfer += proto->serializedStructSize("nebula::VerifyClientVersionResp");
  xfer += proto->serializedFieldSize("error_code", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods<
      ::apache::thrift::type_class::enumeration,
      ::nebula::ErrorCode>::serializedSize<false>(*proto, obj->errorCode);
  if (obj->errorMsg != nullptr) {
    xfer += proto->serializedFieldSize("error_msg", apache::thrift::protocol::T_STRING, 2);
    xfer += proto->serializedSizeZCBinary(*obj->errorMsg);
  }
  xfer += proto->serializedSizeStop();
  return xfer;
}

}  // namespace thrift
}  // namespace apache
