/**
 * Autogenerated by Thrift for graph.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "graph_metadata.h"
#include <thrift/lib/cpp2/visitation/for_each.h>

namespace apache {
namespace thrift {
namespace detail {

template <>
struct ForEachField<::nebula::graph::cpp2::ProfilingStats> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).rows_ref()...);
    f(1, static_cast<T&&>(t).exec_duration_in_us_ref()...);
    f(2, static_cast<T&&>(t).total_duration_in_us_ref()...);
    f(3, static_cast<T&&>(t).other_stats_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::PlanNodeBranchInfo> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).is_do_branch_ref()...);
    f(1, static_cast<T&&>(t).condition_node_id_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::Pair> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).key_ref()...);
    f(1, static_cast<T&&>(t).value_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::PlanNodeDescription> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).name_ref()...);
    f(1, static_cast<T&&>(t).id_ref()...);
    f(2, static_cast<T&&>(t).output_var_ref()...);
    f(3, static_cast<T&&>(t).description_ref()...);
    f(4, static_cast<T&&>(t).profiles_ref()...);
    f(5, static_cast<T&&>(t).branch_info_ref()...);
    f(6, static_cast<T&&>(t).dependencies_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::PlanDescription> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).plan_node_descs_ref()...);
    f(1, static_cast<T&&>(t).node_index_map_ref()...);
    f(2, static_cast<T&&>(t).format_ref()...);
    f(3, static_cast<T&&>(t).optimize_time_in_us_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::ExecutionResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).error_code_ref()...);
    f(1, static_cast<T&&>(t).latency_in_us_ref()...);
    f(2, static_cast<T&&>(t).data_ref()...);
    f(3, static_cast<T&&>(t).space_name_ref()...);
    f(4, static_cast<T&&>(t).error_msg_ref()...);
    f(5, static_cast<T&&>(t).plan_desc_ref()...);
    f(6, static_cast<T&&>(t).comment_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::AuthResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).error_code_ref()...);
    f(1, static_cast<T&&>(t).error_msg_ref()...);
    f(2, static_cast<T&&>(t).session_id_ref()...);
    f(3, static_cast<T&&>(t).time_zone_offset_seconds_ref()...);
    f(4, static_cast<T&&>(t).time_zone_name_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::VerifyClientVersionResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).error_code_ref()...);
    f(1, static_cast<T&&>(t).error_msg_ref()...);
  }
};

template <>
struct ForEachField<::nebula::graph::cpp2::VerifyClientVersionReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).version_ref()...);
  }
};
} // namespace detail
} // namespace thrift
} // namespace apache
