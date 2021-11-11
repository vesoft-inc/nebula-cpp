/**
 * Autogenerated by Thrift for storage.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "storage_metadata.h"
#include <thrift/lib/cpp2/visitation/for_each.h>

namespace apache {
namespace thrift {
namespace detail {

template <>
struct ForEachField<::nebula::storage::cpp2::RequestCommon> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).session_id_ref()...);
    f(1, static_cast<T&&>(t).plan_id_ref()...);
    f(2, static_cast<T&&>(t).profile_detail_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::PartitionResult> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).code_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).leader_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ResponseCommon> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).failed_parts_ref()...);
    f(1, static_cast<T&&>(t).latency_in_us_ref()...);
    f(2, static_cast<T&&>(t).latency_detail_us_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::StatProp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).alias_ref()...);
    f(1, static_cast<T&&>(t).prop_ref()...);
    f(2, static_cast<T&&>(t).stat_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::Expr> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).alias_ref()...);
    f(1, static_cast<T&&>(t).expr_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::EdgeProp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).type_ref()...);
    f(1, static_cast<T&&>(t).props_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::VertexProp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).tag_ref()...);
    f(1, static_cast<T&&>(t).props_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::OrderBy> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).prop_ref()...);
    f(1, static_cast<T&&>(t).direction_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::TraverseSpec> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).edge_types_ref()...);
    f(1, static_cast<T&&>(t).edge_direction_ref()...);
    f(2, static_cast<T&&>(t).dedup_ref()...);
    f(3, static_cast<T&&>(t).stat_props_ref()...);
    f(4, static_cast<T&&>(t).vertex_props_ref()...);
    f(5, static_cast<T&&>(t).edge_props_ref()...);
    f(6, static_cast<T&&>(t).expressions_ref()...);
    f(7, static_cast<T&&>(t).order_by_ref()...);
    f(8, static_cast<T&&>(t).random_ref()...);
    f(9, static_cast<T&&>(t).limit_ref()...);
    f(10, static_cast<T&&>(t).filter_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetNeighborsRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).column_names_ref()...);
    f(2, static_cast<T&&>(t).parts_ref()...);
    f(3, static_cast<T&&>(t).traverse_spec_ref()...);
    f(4, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetNeighborsResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).vertices_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ExecResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetPropRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).vertex_props_ref()...);
    f(3, static_cast<T&&>(t).edge_props_ref()...);
    f(4, static_cast<T&&>(t).expressions_ref()...);
    f(5, static_cast<T&&>(t).dedup_ref()...);
    f(6, static_cast<T&&>(t).order_by_ref()...);
    f(7, static_cast<T&&>(t).limit_ref()...);
    f(8, static_cast<T&&>(t).filter_ref()...);
    f(9, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetPropResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).props_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::NewTag> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).tag_id_ref()...);
    f(1, static_cast<T&&>(t).props_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::NewVertex> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).id_ref()...);
    f(1, static_cast<T&&>(t).tags_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::EdgeKey> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).src_ref()...);
    f(1, static_cast<T&&>(t).edge_type_ref()...);
    f(2, static_cast<T&&>(t).ranking_ref()...);
    f(3, static_cast<T&&>(t).dst_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::NewEdge> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).key_ref()...);
    f(1, static_cast<T&&>(t).props_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::AddVerticesRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).prop_names_ref()...);
    f(3, static_cast<T&&>(t).if_not_exists_ref()...);
    f(4, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::AddEdgesRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).prop_names_ref()...);
    f(3, static_cast<T&&>(t).if_not_exists_ref()...);
    f(4, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::DeleteVerticesRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::DeleteEdgesRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::DelTags> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).id_ref()...);
    f(1, static_cast<T&&>(t).tags_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::DeleteTagsRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::UpdateResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).props_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::UpdatedProp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).name_ref()...);
    f(1, static_cast<T&&>(t).value_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::UpdateVertexRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).vertex_id_ref()...);
    f(3, static_cast<T&&>(t).tag_id_ref()...);
    f(4, static_cast<T&&>(t).updated_props_ref()...);
    f(5, static_cast<T&&>(t).insertable_ref()...);
    f(6, static_cast<T&&>(t).return_props_ref()...);
    f(7, static_cast<T&&>(t).condition_ref()...);
    f(8, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::UpdateEdgeRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).edge_key_ref()...);
    f(3, static_cast<T&&>(t).updated_props_ref()...);
    f(4, static_cast<T&&>(t).insertable_ref()...);
    f(5, static_cast<T&&>(t).return_props_ref()...);
    f(6, static_cast<T&&>(t).condition_ref()...);
    f(7, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetUUIDReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).name_ref()...);
    f(3, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetUUIDResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).id_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::LookupIndexResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).data_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::IndexColumnHint> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).column_name_ref()...);
    f(1, static_cast<T&&>(t).scan_type_ref()...);
    f(2, static_cast<T&&>(t).begin_value_ref()...);
    f(3, static_cast<T&&>(t).end_value_ref()...);
    f(4, static_cast<T&&>(t).include_begin_ref()...);
    f(5, static_cast<T&&>(t).include_end_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::IndexQueryContext> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).index_id_ref()...);
    f(1, static_cast<T&&>(t).filter_ref()...);
    f(2, static_cast<T&&>(t).column_hints_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::IndexSpec> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).contexts_ref()...);
    f(1, static_cast<T&&>(t).schema_id_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::LookupIndexRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).indices_ref()...);
    f(3, static_cast<T&&>(t).return_columns_ref()...);
    f(4, static_cast<T&&>(t).common_ref()...);
    f(5, static_cast<T&&>(t).limit_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::LookupAndTraverseRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).indices_ref()...);
    f(3, static_cast<T&&>(t).traverse_spec_ref()...);
    f(4, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ScanVertexRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).cursor_ref()...);
    f(3, static_cast<T&&>(t).return_columns_ref()...);
    f(4, static_cast<T&&>(t).limit_ref()...);
    f(5, static_cast<T&&>(t).start_time_ref()...);
    f(6, static_cast<T&&>(t).end_time_ref()...);
    f(7, static_cast<T&&>(t).filter_ref()...);
    f(8, static_cast<T&&>(t).only_latest_version_ref()...);
    f(9, static_cast<T&&>(t).enable_read_from_follower_ref()...);
    f(10, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ScanVertexResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).vertex_data_ref()...);
    f(2, static_cast<T&&>(t).has_next_ref()...);
    f(3, static_cast<T&&>(t).next_cursor_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ScanEdgeRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).cursor_ref()...);
    f(3, static_cast<T&&>(t).return_columns_ref()...);
    f(4, static_cast<T&&>(t).limit_ref()...);
    f(5, static_cast<T&&>(t).start_time_ref()...);
    f(6, static_cast<T&&>(t).end_time_ref()...);
    f(7, static_cast<T&&>(t).filter_ref()...);
    f(8, static_cast<T&&>(t).only_latest_version_ref()...);
    f(9, static_cast<T&&>(t).enable_read_from_follower_ref()...);
    f(10, static_cast<T&&>(t).common_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ScanEdgeResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).edge_data_ref()...);
    f(2, static_cast<T&&>(t).has_next_ref()...);
    f(3, static_cast<T&&>(t).next_cursor_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::TaskPara> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).task_specfic_paras_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::AddAdminTaskRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).cmd_ref()...);
    f(1, static_cast<T&&>(t).job_id_ref()...);
    f(2, static_cast<T&&>(t).task_id_ref()...);
    f(3, static_cast<T&&>(t).para_ref()...);
    f(4, static_cast<T&&>(t).concurrency_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::StopAdminTaskRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).job_id_ref()...);
    f(1, static_cast<T&&>(t).task_id_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::AdminExecResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).stats_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::TransLeaderReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).new_leader_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::AddPartReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).as_learner_ref()...);
    f(3, static_cast<T&&>(t).peers_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::AddLearnerReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).learner_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::RemovePartReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::MemberChangeReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).peer_ref()...);
    f(3, static_cast<T&&>(t).add_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::CatchUpDataReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).target_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetLeaderReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::CreateCPRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).name_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::DropCPRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).name_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::BlockingSignRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).sign_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::GetLeaderPartsResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).leader_parts_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::CheckPeersReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).part_id_ref()...);
    f(2, static_cast<T&&>(t).peers_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::RebuildIndexRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).index_id_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::CreateCPResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).info_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ListClusterInfoResp> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).dir_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ListClusterInfoReq> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::KVGetRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).return_partly_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::KVGetResponse> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).result_ref()...);
    f(1, static_cast<T&&>(t).key_values_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::KVPutRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::KVRemoveRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::InternalTxnRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).txn_id_ref()...);
    f(1, static_cast<T&&>(t).term_of_parts_ref()...);
    f(2, static_cast<T&&>(t).add_edge_req_ref()...);
    f(3, static_cast<T&&>(t).upd_edge_req_ref()...);
    f(4, static_cast<T&&>(t).edge_ver_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ChainAddEdgesRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).space_id_ref()...);
    f(1, static_cast<T&&>(t).parts_ref()...);
    f(2, static_cast<T&&>(t).prop_names_ref()...);
    f(3, static_cast<T&&>(t).if_not_exists_ref()...);
    f(4, static_cast<T&&>(t).term_ref()...);
    f(5, static_cast<T&&>(t).edge_version_ref()...);
  }
};

template <>
struct ForEachField<::nebula::storage::cpp2::ChainUpdateEdgeRequest> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).update_edge_request_ref()...);
    f(1, static_cast<T&&>(t).term_ref()...);
    f(2, static_cast<T&&>(t).edge_version_ref()...);
    f(3, static_cast<T&&>(t).space_id_ref()...);
    f(4, static_cast<T&&>(t).parts_ref()...);
  }
};
} // namespace detail
} // namespace thrift
} // namespace apache
