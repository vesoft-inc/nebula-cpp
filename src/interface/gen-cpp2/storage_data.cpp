/**
 * Autogenerated by Thrift for storage.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#include "storage_data.h"

#include <thrift/lib/cpp2/gen/module_data_cpp.h>

namespace apache {
namespace thrift {

const std::array<::nebula::storage::cpp2::StatType, 5> TEnumDataStorage<::nebula::storage::cpp2::StatType>::values = {{
  type::SUM,
  type::COUNT,
  type::AVG,
  type::MAX,
  type::MIN,
}};
const std::array<folly::StringPiece, 5> TEnumDataStorage<::nebula::storage::cpp2::StatType>::names = {{
  "SUM",
  "COUNT",
  "AVG",
  "MAX",
  "MIN",
}};

const std::array<::nebula::storage::cpp2::OrderDirection, 2> TEnumDataStorage<::nebula::storage::cpp2::OrderDirection>::values = {{
  type::ASCENDING,
  type::DESCENDING,
}};
const std::array<folly::StringPiece, 2> TEnumDataStorage<::nebula::storage::cpp2::OrderDirection>::names = {{
  "ASCENDING",
  "DESCENDING",
}};

const std::array<::nebula::storage::cpp2::EdgeDirection, 3> TEnumDataStorage<::nebula::storage::cpp2::EdgeDirection>::values = {{
  type::BOTH,
  type::IN_EDGE,
  type::OUT_EDGE,
}};
const std::array<folly::StringPiece, 3> TEnumDataStorage<::nebula::storage::cpp2::EdgeDirection>::names = {{
  "BOTH",
  "IN_EDGE",
  "OUT_EDGE",
}};

const std::array<::nebula::storage::cpp2::ScanType, 2> TEnumDataStorage<::nebula::storage::cpp2::ScanType>::values = {{
  type::PREFIX,
  type::RANGE,
}};
const std::array<folly::StringPiece, 2> TEnumDataStorage<::nebula::storage::cpp2::ScanType>::names = {{
  "PREFIX",
  "RANGE",
}};

const std::array<::nebula::storage::cpp2::EngineSignType, 2> TEnumDataStorage<::nebula::storage::cpp2::EngineSignType>::values = {{
  type::BLOCK_ON,
  type::BLOCK_OFF,
}};
const std::array<folly::StringPiece, 2> TEnumDataStorage<::nebula::storage::cpp2::EngineSignType>::names = {{
  "BLOCK_ON",
  "BLOCK_OFF",
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::RequestCommon>::fields_names = {{
  "session_id",
  "plan_id",
  "profile_detail",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::RequestCommon>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::RequestCommon>::fields_types = {{
  TType::T_I64,
  TType::T_I64,
  TType::T_BOOL,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::PartitionResult>::fields_names = {{
  "code",
  "part_id",
  "leader",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::PartitionResult>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::PartitionResult>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::ResponseCommon>::fields_names = {{
  "failed_parts",
  "latency_in_us",
  "latency_detail_us",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::ResponseCommon>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::ResponseCommon>::fields_types = {{
  TType::T_LIST,
  TType::T_I32,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::StatProp>::fields_names = {{
  "alias",
  "prop",
  "stat",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::StatProp>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::StatProp>::fields_types = {{
  TType::T_STRING,
  TType::T_STRING,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::Expr>::fields_names = {{
  "alias",
  "expr",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::Expr>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::Expr>::fields_types = {{
  TType::T_STRING,
  TType::T_STRING,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::EdgeProp>::fields_names = {{
  "type",
  "props",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::EdgeProp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::EdgeProp>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::VertexProp>::fields_names = {{
  "tag",
  "props",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::VertexProp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::VertexProp>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::OrderBy>::fields_names = {{
  "prop",
  "direction",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::OrderBy>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::OrderBy>::fields_types = {{
  TType::T_STRING,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 11> TStructDataStorage<::nebula::storage::cpp2::TraverseSpec>::fields_names = {{
  "edge_types",
  "edge_direction",
  "dedup",
  "stat_props",
  "vertex_props",
  "edge_props",
  "expressions",
  "order_by",
  "random",
  "limit",
  "filter",
}};
const std::array<int16_t, 11> TStructDataStorage<::nebula::storage::cpp2::TraverseSpec>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
}};
const std::array<protocol::TType, 11> TStructDataStorage<::nebula::storage::cpp2::TraverseSpec>::fields_types = {{
  TType::T_LIST,
  TType::T_I32,
  TType::T_BOOL,
  TType::T_LIST,
  TType::T_LIST,
  TType::T_LIST,
  TType::T_LIST,
  TType::T_LIST,
  TType::T_BOOL,
  TType::T_I64,
  TType::T_STRING,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::GetNeighborsRequest>::fields_names = {{
  "space_id",
  "column_names",
  "parts",
  "traverse_spec",
  "common",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::GetNeighborsRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::GetNeighborsRequest>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
  TType::T_MAP,
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::GetNeighborsResponse>::fields_names = {{
  "result",
  "vertices",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::GetNeighborsResponse>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::GetNeighborsResponse>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 1> TStructDataStorage<::nebula::storage::cpp2::ExecResponse>::fields_names = {{
  "result",
}};
const std::array<int16_t, 1> TStructDataStorage<::nebula::storage::cpp2::ExecResponse>::fields_ids = {{
  1,
}};
const std::array<protocol::TType, 1> TStructDataStorage<::nebula::storage::cpp2::ExecResponse>::fields_types = {{
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 10> TStructDataStorage<::nebula::storage::cpp2::GetPropRequest>::fields_names = {{
  "space_id",
  "parts",
  "vertex_props",
  "edge_props",
  "expressions",
  "dedup",
  "order_by",
  "limit",
  "filter",
  "common",
}};
const std::array<int16_t, 10> TStructDataStorage<::nebula::storage::cpp2::GetPropRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
}};
const std::array<protocol::TType, 10> TStructDataStorage<::nebula::storage::cpp2::GetPropRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_LIST,
  TType::T_LIST,
  TType::T_LIST,
  TType::T_BOOL,
  TType::T_LIST,
  TType::T_I64,
  TType::T_STRING,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::GetPropResponse>::fields_names = {{
  "result",
  "props",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::GetPropResponse>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::GetPropResponse>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::NewTag>::fields_names = {{
  "tag_id",
  "props",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::NewTag>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::NewTag>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::NewVertex>::fields_names = {{
  "id",
  "tags",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::NewVertex>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::NewVertex>::fields_types = {{
  TType::T_STRUCT,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 4> TStructDataStorage<::nebula::storage::cpp2::EdgeKey>::fields_names = {{
  "src",
  "edge_type",
  "ranking",
  "dst",
}};
const std::array<int16_t, 4> TStructDataStorage<::nebula::storage::cpp2::EdgeKey>::fields_ids = {{
  1,
  2,
  3,
  4,
}};
const std::array<protocol::TType, 4> TStructDataStorage<::nebula::storage::cpp2::EdgeKey>::fields_types = {{
  TType::T_STRUCT,
  TType::T_I32,
  TType::T_I64,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::NewEdge>::fields_names = {{
  "key",
  "props",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::NewEdge>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::NewEdge>::fields_types = {{
  TType::T_STRUCT,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::AddVerticesRequest>::fields_names = {{
  "space_id",
  "parts",
  "prop_names",
  "if_not_exists",
  "common",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::AddVerticesRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::AddVerticesRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_MAP,
  TType::T_BOOL,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::AddEdgesRequest>::fields_names = {{
  "space_id",
  "parts",
  "prop_names",
  "if_not_exists",
  "common",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::AddEdgesRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::AddEdgesRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_LIST,
  TType::T_BOOL,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteVerticesRequest>::fields_names = {{
  "space_id",
  "parts",
  "common",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteVerticesRequest>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteVerticesRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteEdgesRequest>::fields_names = {{
  "space_id",
  "parts",
  "common",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteEdgesRequest>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteEdgesRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::DelTags>::fields_names = {{
  "id",
  "tags",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::DelTags>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::DelTags>::fields_types = {{
  TType::T_STRUCT,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteTagsRequest>::fields_names = {{
  "space_id",
  "parts",
  "common",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteTagsRequest>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::DeleteTagsRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::UpdateResponse>::fields_names = {{
  "result",
  "props",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::UpdateResponse>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::UpdateResponse>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::UpdatedProp>::fields_names = {{
  "name",
  "value",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::UpdatedProp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::UpdatedProp>::fields_types = {{
  TType::T_STRING,
  TType::T_STRING,
}};

const std::array<folly::StringPiece, 9> TStructDataStorage<::nebula::storage::cpp2::UpdateVertexRequest>::fields_names = {{
  "space_id",
  "part_id",
  "vertex_id",
  "tag_id",
  "updated_props",
  "insertable",
  "return_props",
  "condition",
  "common",
}};
const std::array<int16_t, 9> TStructDataStorage<::nebula::storage::cpp2::UpdateVertexRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
}};
const std::array<protocol::TType, 9> TStructDataStorage<::nebula::storage::cpp2::UpdateVertexRequest>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
  TType::T_I32,
  TType::T_LIST,
  TType::T_BOOL,
  TType::T_LIST,
  TType::T_STRING,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 8> TStructDataStorage<::nebula::storage::cpp2::UpdateEdgeRequest>::fields_names = {{
  "space_id",
  "part_id",
  "edge_key",
  "updated_props",
  "insertable",
  "return_props",
  "condition",
  "common",
}};
const std::array<int16_t, 8> TStructDataStorage<::nebula::storage::cpp2::UpdateEdgeRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
}};
const std::array<protocol::TType, 8> TStructDataStorage<::nebula::storage::cpp2::UpdateEdgeRequest>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
  TType::T_LIST,
  TType::T_BOOL,
  TType::T_LIST,
  TType::T_STRING,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 4> TStructDataStorage<::nebula::storage::cpp2::GetUUIDReq>::fields_names = {{
  "space_id",
  "part_id",
  "name",
  "common",
}};
const std::array<int16_t, 4> TStructDataStorage<::nebula::storage::cpp2::GetUUIDReq>::fields_ids = {{
  1,
  2,
  3,
  4,
}};
const std::array<protocol::TType, 4> TStructDataStorage<::nebula::storage::cpp2::GetUUIDReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRING,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::GetUUIDResp>::fields_names = {{
  "result",
  "id",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::GetUUIDResp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::GetUUIDResp>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::LookupIndexResp>::fields_names = {{
  "result",
  "data",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::LookupIndexResp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::LookupIndexResp>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 6> TStructDataStorage<::nebula::storage::cpp2::IndexColumnHint>::fields_names = {{
  "column_name",
  "scan_type",
  "begin_value",
  "end_value",
  "include_begin",
  "include_end",
}};
const std::array<int16_t, 6> TStructDataStorage<::nebula::storage::cpp2::IndexColumnHint>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
}};
const std::array<protocol::TType, 6> TStructDataStorage<::nebula::storage::cpp2::IndexColumnHint>::fields_types = {{
  TType::T_STRING,
  TType::T_I32,
  TType::T_STRUCT,
  TType::T_STRUCT,
  TType::T_BOOL,
  TType::T_BOOL,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::IndexQueryContext>::fields_names = {{
  "index_id",
  "filter",
  "column_hints",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::IndexQueryContext>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::IndexQueryContext>::fields_types = {{
  TType::T_I32,
  TType::T_STRING,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::IndexSpec>::fields_names = {{
  "contexts",
  "schema_id",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::IndexSpec>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::IndexSpec>::fields_types = {{
  TType::T_LIST,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 6> TStructDataStorage<::nebula::storage::cpp2::LookupIndexRequest>::fields_names = {{
  "space_id",
  "parts",
  "indices",
  "return_columns",
  "common",
  "limit",
}};
const std::array<int16_t, 6> TStructDataStorage<::nebula::storage::cpp2::LookupIndexRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
}};
const std::array<protocol::TType, 6> TStructDataStorage<::nebula::storage::cpp2::LookupIndexRequest>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
  TType::T_STRUCT,
  TType::T_LIST,
  TType::T_STRUCT,
  TType::T_I64,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::LookupAndTraverseRequest>::fields_names = {{
  "space_id",
  "parts",
  "indices",
  "traverse_spec",
  "common",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::LookupAndTraverseRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::LookupAndTraverseRequest>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
  TType::T_STRUCT,
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::ScanCursor>::fields_names = {{
  "has_next",
  "next_cursor",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::ScanCursor>::fields_ids = {{
  3,
  4,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::ScanCursor>::fields_types = {{
  TType::T_BOOL,
  TType::T_STRING,
}};

const std::array<folly::StringPiece, 10> TStructDataStorage<::nebula::storage::cpp2::ScanVertexRequest>::fields_names = {{
  "space_id",
  "parts",
  "return_columns",
  "limit",
  "start_time",
  "end_time",
  "filter",
  "only_latest_version",
  "enable_read_from_follower",
  "common",
}};
const std::array<int16_t, 10> TStructDataStorage<::nebula::storage::cpp2::ScanVertexRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
}};
const std::array<protocol::TType, 10> TStructDataStorage<::nebula::storage::cpp2::ScanVertexRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_LIST,
  TType::T_I64,
  TType::T_I64,
  TType::T_I64,
  TType::T_STRING,
  TType::T_BOOL,
  TType::T_BOOL,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::ScanVertexResponse>::fields_names = {{
  "result",
  "vertex_data",
  "cursors",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::ScanVertexResponse>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::ScanVertexResponse>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 10> TStructDataStorage<::nebula::storage::cpp2::ScanEdgeRequest>::fields_names = {{
  "space_id",
  "parts",
  "return_columns",
  "limit",
  "start_time",
  "end_time",
  "filter",
  "only_latest_version",
  "enable_read_from_follower",
  "common",
}};
const std::array<int16_t, 10> TStructDataStorage<::nebula::storage::cpp2::ScanEdgeRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
}};
const std::array<protocol::TType, 10> TStructDataStorage<::nebula::storage::cpp2::ScanEdgeRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_STRUCT,
  TType::T_I64,
  TType::T_I64,
  TType::T_I64,
  TType::T_STRING,
  TType::T_BOOL,
  TType::T_BOOL,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::ScanEdgeResponse>::fields_names = {{
  "result",
  "edge_data",
  "cursors",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::ScanEdgeResponse>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::ScanEdgeResponse>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::TaskPara>::fields_names = {{
  "space_id",
  "parts",
  "task_specific_paras",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::TaskPara>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::TaskPara>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::AddAdminTaskRequest>::fields_names = {{
  "cmd",
  "job_id",
  "task_id",
  "para",
  "concurrency",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::AddAdminTaskRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::AddAdminTaskRequest>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::StopAdminTaskRequest>::fields_names = {{
  "job_id",
  "task_id",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::StopAdminTaskRequest>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::StopAdminTaskRequest>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::AdminExecResp>::fields_names = {{
  "result",
  "stats",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::AdminExecResp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::AdminExecResp>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::TransLeaderReq>::fields_names = {{
  "space_id",
  "part_id",
  "new_leader",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::TransLeaderReq>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::TransLeaderReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 4> TStructDataStorage<::nebula::storage::cpp2::AddPartReq>::fields_names = {{
  "space_id",
  "part_id",
  "as_learner",
  "peers",
}};
const std::array<int16_t, 4> TStructDataStorage<::nebula::storage::cpp2::AddPartReq>::fields_ids = {{
  1,
  2,
  3,
  4,
}};
const std::array<protocol::TType, 4> TStructDataStorage<::nebula::storage::cpp2::AddPartReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_BOOL,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::AddLearnerReq>::fields_names = {{
  "space_id",
  "part_id",
  "learner",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::AddLearnerReq>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::AddLearnerReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::RemovePartReq>::fields_names = {{
  "space_id",
  "part_id",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::RemovePartReq>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::RemovePartReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 4> TStructDataStorage<::nebula::storage::cpp2::MemberChangeReq>::fields_names = {{
  "space_id",
  "part_id",
  "peer",
  "add",
}};
const std::array<int16_t, 4> TStructDataStorage<::nebula::storage::cpp2::MemberChangeReq>::fields_ids = {{
  1,
  2,
  3,
  4,
}};
const std::array<protocol::TType, 4> TStructDataStorage<::nebula::storage::cpp2::MemberChangeReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
  TType::T_BOOL,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::CatchUpDataReq>::fields_names = {{
  "space_id",
  "part_id",
  "target",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::CatchUpDataReq>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::CatchUpDataReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 0> TStructDataStorage<::nebula::storage::cpp2::GetLeaderReq>::fields_names = {{
}};
const std::array<int16_t, 0> TStructDataStorage<::nebula::storage::cpp2::GetLeaderReq>::fields_ids = {{
}};
const std::array<protocol::TType, 0> TStructDataStorage<::nebula::storage::cpp2::GetLeaderReq>::fields_types = {{
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::CreateCPRequest>::fields_names = {{
  "space_id",
  "name",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::CreateCPRequest>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::CreateCPRequest>::fields_types = {{
  TType::T_I32,
  TType::T_STRING,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::DropCPRequest>::fields_names = {{
  "space_id",
  "name",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::DropCPRequest>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::DropCPRequest>::fields_types = {{
  TType::T_I32,
  TType::T_STRING,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::BlockingSignRequest>::fields_names = {{
  "space_id",
  "sign",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::BlockingSignRequest>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::BlockingSignRequest>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::GetLeaderPartsResp>::fields_names = {{
  "result",
  "leader_parts",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::GetLeaderPartsResp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::GetLeaderPartsResp>::fields_types = {{
  TType::T_STRUCT,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::CheckPeersReq>::fields_names = {{
  "space_id",
  "part_id",
  "peers",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::CheckPeersReq>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::CheckPeersReq>::fields_types = {{
  TType::T_I32,
  TType::T_I32,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::RebuildIndexRequest>::fields_names = {{
  "space_id",
  "parts",
  "index_id",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::RebuildIndexRequest>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::RebuildIndexRequest>::fields_types = {{
  TType::T_I32,
  TType::T_LIST,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::CreateCPResp>::fields_names = {{
  "result",
  "info",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::CreateCPResp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::CreateCPResp>::fields_types = {{
  TType::T_STRUCT,
  TType::T_LIST,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::ListClusterInfoResp>::fields_names = {{
  "result",
  "dir",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::ListClusterInfoResp>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::ListClusterInfoResp>::fields_types = {{
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

const std::array<folly::StringPiece, 0> TStructDataStorage<::nebula::storage::cpp2::ListClusterInfoReq>::fields_names = {{
}};
const std::array<int16_t, 0> TStructDataStorage<::nebula::storage::cpp2::ListClusterInfoReq>::fields_ids = {{
}};
const std::array<protocol::TType, 0> TStructDataStorage<::nebula::storage::cpp2::ListClusterInfoReq>::fields_types = {{
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::nebula::storage::cpp2::KVGetRequest>::fields_names = {{
  "space_id",
  "parts",
  "return_partly",
}};
const std::array<int16_t, 3> TStructDataStorage<::nebula::storage::cpp2::KVGetRequest>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::nebula::storage::cpp2::KVGetRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_BOOL,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::KVGetResponse>::fields_names = {{
  "result",
  "key_values",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::KVGetResponse>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::KVGetResponse>::fields_types = {{
  TType::T_STRUCT,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::KVPutRequest>::fields_names = {{
  "space_id",
  "parts",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::KVPutRequest>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::KVPutRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 2> TStructDataStorage<::nebula::storage::cpp2::KVRemoveRequest>::fields_names = {{
  "space_id",
  "parts",
}};
const std::array<int16_t, 2> TStructDataStorage<::nebula::storage::cpp2::KVRemoveRequest>::fields_ids = {{
  1,
  2,
}};
const std::array<protocol::TType, 2> TStructDataStorage<::nebula::storage::cpp2::KVRemoveRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::InternalTxnRequest>::fields_names = {{
  "txn_id",
  "term_of_parts",
  "add_edge_req",
  "upd_edge_req",
  "edge_ver",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::InternalTxnRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::InternalTxnRequest>::fields_types = {{
  TType::T_I64,
  TType::T_MAP,
  TType::T_STRUCT,
  TType::T_STRUCT,
  TType::T_MAP,
}};

const std::array<folly::StringPiece, 6> TStructDataStorage<::nebula::storage::cpp2::ChainAddEdgesRequest>::fields_names = {{
  "space_id",
  "parts",
  "prop_names",
  "if_not_exists",
  "term",
  "edge_version",
}};
const std::array<int16_t, 6> TStructDataStorage<::nebula::storage::cpp2::ChainAddEdgesRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
  6,
}};
const std::array<protocol::TType, 6> TStructDataStorage<::nebula::storage::cpp2::ChainAddEdgesRequest>::fields_types = {{
  TType::T_I32,
  TType::T_MAP,
  TType::T_LIST,
  TType::T_BOOL,
  TType::T_I64,
  TType::T_I64,
}};

const std::array<folly::StringPiece, 5> TStructDataStorage<::nebula::storage::cpp2::ChainUpdateEdgeRequest>::fields_names = {{
  "update_edge_request",
  "term",
  "edge_version",
  "space_id",
  "parts",
}};
const std::array<int16_t, 5> TStructDataStorage<::nebula::storage::cpp2::ChainUpdateEdgeRequest>::fields_ids = {{
  1,
  2,
  3,
  4,
  5,
}};
const std::array<protocol::TType, 5> TStructDataStorage<::nebula::storage::cpp2::ChainUpdateEdgeRequest>::fields_types = {{
  TType::T_STRUCT,
  TType::T_I64,
  TType::T_I64,
  TType::T_I32,
  TType::T_LIST,
}};

} // namespace thrift
} // namespace apache
