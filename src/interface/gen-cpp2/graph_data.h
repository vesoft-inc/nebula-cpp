/**
 * Autogenerated by Thrift for graph.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/module_data_h.h>

#include "graph_types.h"

namespace apache { namespace thrift {

template <> struct TStructDataStorage<::nebula::graph::cpp2::ProfilingStats> {
  static constexpr const std::size_t fields_size = 4;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::PlanNodeBranchInfo> {
  static constexpr const std::size_t fields_size = 2;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::Pair> {
  static constexpr const std::size_t fields_size = 2;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::PlanNodeDescription> {
  static constexpr const std::size_t fields_size = 7;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::PlanDescription> {
  static constexpr const std::size_t fields_size = 4;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::ExecutionResponse> {
  static constexpr const std::size_t fields_size = 7;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::AuthResponse> {
  static constexpr const std::size_t fields_size = 5;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::VerifyClientVersionResp> {
  static constexpr const std::size_t fields_size = 2;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

template <> struct TStructDataStorage<::nebula::graph::cpp2::VerifyClientVersionReq> {
  static constexpr const std::size_t fields_size = 1;
  static const std::array<folly::StringPiece, fields_size> fields_names;
  static const std::array<int16_t, fields_size> fields_ids;
  static const std::array<protocol::TType, fields_size> fields_types;
};

}} // apache::thrift
