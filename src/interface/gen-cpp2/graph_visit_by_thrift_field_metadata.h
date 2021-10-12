/**
 * Autogenerated by Thrift for graph.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/visitation/visit_by_thrift_field_metadata.h>
#include "graph_metadata.h"

namespace apache {
namespace thrift {
namespace detail {

template <>
struct VisitByThriftId<::nebula::graph::cpp2::ProfilingStats> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).rows_ref());
    case 2:
      return f(1, static_cast<T&&>(t).exec_duration_in_us_ref());
    case 3:
      return f(2, static_cast<T&&>(t).total_duration_in_us_ref());
    case 4:
      return f(3, static_cast<T&&>(t).other_stats_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::ProfilingStats");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::PlanNodeBranchInfo> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).is_do_branch_ref());
    case 2:
      return f(1, static_cast<T&&>(t).condition_node_id_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::PlanNodeBranchInfo");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::Pair> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).key_ref());
    case 2:
      return f(1, static_cast<T&&>(t).value_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::Pair");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::PlanNodeDescription> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).name_ref());
    case 2:
      return f(1, static_cast<T&&>(t).id_ref());
    case 3:
      return f(2, static_cast<T&&>(t).output_var_ref());
    case 4:
      return f(3, static_cast<T&&>(t).description_ref());
    case 5:
      return f(4, static_cast<T&&>(t).profiles_ref());
    case 6:
      return f(5, static_cast<T&&>(t).branch_info_ref());
    case 7:
      return f(6, static_cast<T&&>(t).dependencies_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::PlanNodeDescription");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::PlanDescription> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).plan_node_descs_ref());
    case 2:
      return f(1, static_cast<T&&>(t).node_index_map_ref());
    case 3:
      return f(2, static_cast<T&&>(t).format_ref());
    case 4:
      return f(3, static_cast<T&&>(t).optimize_time_in_us_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::PlanDescription");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::ExecutionResponse> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).error_code_ref());
    case 2:
      return f(1, static_cast<T&&>(t).latency_in_us_ref());
    case 3:
      return f(2, static_cast<T&&>(t).data_ref());
    case 4:
      return f(3, static_cast<T&&>(t).space_name_ref());
    case 5:
      return f(4, static_cast<T&&>(t).error_msg_ref());
    case 6:
      return f(5, static_cast<T&&>(t).plan_desc_ref());
    case 7:
      return f(6, static_cast<T&&>(t).comment_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::ExecutionResponse");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::AuthResponse> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).error_code_ref());
    case 2:
      return f(1, static_cast<T&&>(t).error_msg_ref());
    case 3:
      return f(2, static_cast<T&&>(t).session_id_ref());
    case 4:
      return f(3, static_cast<T&&>(t).time_zone_offset_seconds_ref());
    case 5:
      return f(4, static_cast<T&&>(t).time_zone_name_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::AuthResponse");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::VerifyClientVersionResp> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).error_code_ref());
    case 2:
      return f(1, static_cast<T&&>(t).error_msg_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::VerifyClientVersionResp");
    }
  }
};

template <>
struct VisitByThriftId<::nebula::graph::cpp2::VerifyClientVersionReq> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, size_t id, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (id) {
    case 1:
      return f(0, static_cast<T&&>(t).version_ref());
    default:
      throwInvalidThriftId(id, "::nebula::graph::cpp2::VerifyClientVersionReq");
    }
  }
};
} // namespace detail
} // namespace thrift
} // namespace apache
