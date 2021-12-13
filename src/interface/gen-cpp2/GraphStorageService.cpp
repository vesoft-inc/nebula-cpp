/**
 * Autogenerated by Thrift for storage.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "GraphStorageService.h"
#include "GraphStorageService.tcc"
#include "storage_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace nebula { namespace storage { namespace cpp2 {
std::unique_ptr<apache::thrift::AsyncProcessor> GraphStorageServiceSvIf::getProcessor() {
  return std::make_unique<GraphStorageServiceAsyncProcessor>(this);
}


void GraphStorageServiceSvIf::getNeighbors( ::nebula::storage::cpp2::GetNeighborsResponse& /*_return*/, const  ::nebula::storage::cpp2::GetNeighborsRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getNeighbors");
}

folly::SemiFuture< ::nebula::storage::cpp2::GetNeighborsResponse> GraphStorageServiceSvIf::semifuture_getNeighbors(const  ::nebula::storage::cpp2::GetNeighborsRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::GetNeighborsResponse& _return) { getNeighbors(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::GetNeighborsResponse> GraphStorageServiceSvIf::future_getNeighbors(const  ::nebula::storage::cpp2::GetNeighborsRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_getNeighbors(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_getNeighbors(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::GetNeighborsResponse>> callback, const  ::nebula::storage::cpp2::GetNeighborsRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_getNeighbors(p_req);
  });
}

void GraphStorageServiceSvIf::getProps( ::nebula::storage::cpp2::GetPropResponse& /*_return*/, const  ::nebula::storage::cpp2::GetPropRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getProps");
}

folly::SemiFuture< ::nebula::storage::cpp2::GetPropResponse> GraphStorageServiceSvIf::semifuture_getProps(const  ::nebula::storage::cpp2::GetPropRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::GetPropResponse& _return) { getProps(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::GetPropResponse> GraphStorageServiceSvIf::future_getProps(const  ::nebula::storage::cpp2::GetPropRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_getProps(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_getProps(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::GetPropResponse>> callback, const  ::nebula::storage::cpp2::GetPropRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_getProps(p_req);
  });
}

void GraphStorageServiceSvIf::addVertices( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::AddVerticesRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("addVertices");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_addVertices(const  ::nebula::storage::cpp2::AddVerticesRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { addVertices(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_addVertices(const  ::nebula::storage::cpp2::AddVerticesRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_addVertices(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_addVertices(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::AddVerticesRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_addVertices(p_req);
  });
}

void GraphStorageServiceSvIf::addEdges( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::AddEdgesRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("addEdges");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_addEdges(const  ::nebula::storage::cpp2::AddEdgesRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { addEdges(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_addEdges(const  ::nebula::storage::cpp2::AddEdgesRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_addEdges(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_addEdges(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::AddEdgesRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_addEdges(p_req);
  });
}

void GraphStorageServiceSvIf::deleteEdges( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::DeleteEdgesRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("deleteEdges");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_deleteEdges(const  ::nebula::storage::cpp2::DeleteEdgesRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { deleteEdges(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_deleteEdges(const  ::nebula::storage::cpp2::DeleteEdgesRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_deleteEdges(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_deleteEdges(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::DeleteEdgesRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_deleteEdges(p_req);
  });
}

void GraphStorageServiceSvIf::deleteVertices( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::DeleteVerticesRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("deleteVertices");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_deleteVertices(const  ::nebula::storage::cpp2::DeleteVerticesRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { deleteVertices(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_deleteVertices(const  ::nebula::storage::cpp2::DeleteVerticesRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_deleteVertices(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_deleteVertices(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::DeleteVerticesRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_deleteVertices(p_req);
  });
}

void GraphStorageServiceSvIf::deleteTags( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::DeleteTagsRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("deleteTags");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_deleteTags(const  ::nebula::storage::cpp2::DeleteTagsRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { deleteTags(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_deleteTags(const  ::nebula::storage::cpp2::DeleteTagsRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_deleteTags(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_deleteTags(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::DeleteTagsRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_deleteTags(p_req);
  });
}

void GraphStorageServiceSvIf::updateVertex( ::nebula::storage::cpp2::UpdateResponse& /*_return*/, const  ::nebula::storage::cpp2::UpdateVertexRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("updateVertex");
}

folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> GraphStorageServiceSvIf::semifuture_updateVertex(const  ::nebula::storage::cpp2::UpdateVertexRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::UpdateResponse& _return) { updateVertex(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::UpdateResponse> GraphStorageServiceSvIf::future_updateVertex(const  ::nebula::storage::cpp2::UpdateVertexRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_updateVertex(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_updateVertex(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::UpdateResponse>> callback, const  ::nebula::storage::cpp2::UpdateVertexRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_updateVertex(p_req);
  });
}

void GraphStorageServiceSvIf::updateEdge( ::nebula::storage::cpp2::UpdateResponse& /*_return*/, const  ::nebula::storage::cpp2::UpdateEdgeRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("updateEdge");
}

folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> GraphStorageServiceSvIf::semifuture_updateEdge(const  ::nebula::storage::cpp2::UpdateEdgeRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::UpdateResponse& _return) { updateEdge(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::UpdateResponse> GraphStorageServiceSvIf::future_updateEdge(const  ::nebula::storage::cpp2::UpdateEdgeRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_updateEdge(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_updateEdge(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::UpdateResponse>> callback, const  ::nebula::storage::cpp2::UpdateEdgeRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_updateEdge(p_req);
  });
}

void GraphStorageServiceSvIf::scanVertex( ::nebula::storage::cpp2::ScanResponse& /*_return*/, const  ::nebula::storage::cpp2::ScanVertexRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("scanVertex");
}

folly::SemiFuture< ::nebula::storage::cpp2::ScanResponse> GraphStorageServiceSvIf::semifuture_scanVertex(const  ::nebula::storage::cpp2::ScanVertexRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ScanResponse& _return) { scanVertex(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ScanResponse> GraphStorageServiceSvIf::future_scanVertex(const  ::nebula::storage::cpp2::ScanVertexRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_scanVertex(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_scanVertex(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ScanResponse>> callback, const  ::nebula::storage::cpp2::ScanVertexRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_scanVertex(p_req);
  });
}

void GraphStorageServiceSvIf::scanEdge( ::nebula::storage::cpp2::ScanResponse& /*_return*/, const  ::nebula::storage::cpp2::ScanEdgeRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("scanEdge");
}

folly::SemiFuture< ::nebula::storage::cpp2::ScanResponse> GraphStorageServiceSvIf::semifuture_scanEdge(const  ::nebula::storage::cpp2::ScanEdgeRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ScanResponse& _return) { scanEdge(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ScanResponse> GraphStorageServiceSvIf::future_scanEdge(const  ::nebula::storage::cpp2::ScanEdgeRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_scanEdge(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_scanEdge(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ScanResponse>> callback, const  ::nebula::storage::cpp2::ScanEdgeRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_scanEdge(p_req);
  });
}

void GraphStorageServiceSvIf::getUUID( ::nebula::storage::cpp2::GetUUIDResp& /*_return*/, const  ::nebula::storage::cpp2::GetUUIDReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getUUID");
}

folly::SemiFuture< ::nebula::storage::cpp2::GetUUIDResp> GraphStorageServiceSvIf::semifuture_getUUID(const  ::nebula::storage::cpp2::GetUUIDReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::GetUUIDResp& _return) { getUUID(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::GetUUIDResp> GraphStorageServiceSvIf::future_getUUID(const  ::nebula::storage::cpp2::GetUUIDReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_getUUID(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_getUUID(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::GetUUIDResp>> callback, const  ::nebula::storage::cpp2::GetUUIDReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_getUUID(p_req);
  });
}

void GraphStorageServiceSvIf::lookupIndex( ::nebula::storage::cpp2::LookupIndexResp& /*_return*/, const  ::nebula::storage::cpp2::LookupIndexRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("lookupIndex");
}

folly::SemiFuture< ::nebula::storage::cpp2::LookupIndexResp> GraphStorageServiceSvIf::semifuture_lookupIndex(const  ::nebula::storage::cpp2::LookupIndexRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::LookupIndexResp& _return) { lookupIndex(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::LookupIndexResp> GraphStorageServiceSvIf::future_lookupIndex(const  ::nebula::storage::cpp2::LookupIndexRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_lookupIndex(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_lookupIndex(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::LookupIndexResp>> callback, const  ::nebula::storage::cpp2::LookupIndexRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_lookupIndex(p_req);
  });
}

void GraphStorageServiceSvIf::lookupAndTraverse( ::nebula::storage::cpp2::GetNeighborsResponse& /*_return*/, const  ::nebula::storage::cpp2::LookupAndTraverseRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("lookupAndTraverse");
}

folly::SemiFuture< ::nebula::storage::cpp2::GetNeighborsResponse> GraphStorageServiceSvIf::semifuture_lookupAndTraverse(const  ::nebula::storage::cpp2::LookupAndTraverseRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::GetNeighborsResponse& _return) { lookupAndTraverse(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::GetNeighborsResponse> GraphStorageServiceSvIf::future_lookupAndTraverse(const  ::nebula::storage::cpp2::LookupAndTraverseRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_lookupAndTraverse(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_lookupAndTraverse(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::GetNeighborsResponse>> callback, const  ::nebula::storage::cpp2::LookupAndTraverseRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_lookupAndTraverse(p_req);
  });
}

void GraphStorageServiceSvIf::chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& /*_return*/, const  ::nebula::storage::cpp2::UpdateEdgeRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("chainUpdateEdge");
}

folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> GraphStorageServiceSvIf::semifuture_chainUpdateEdge(const  ::nebula::storage::cpp2::UpdateEdgeRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::UpdateResponse& _return) { chainUpdateEdge(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::UpdateResponse> GraphStorageServiceSvIf::future_chainUpdateEdge(const  ::nebula::storage::cpp2::UpdateEdgeRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_chainUpdateEdge(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_chainUpdateEdge(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::UpdateResponse>> callback, const  ::nebula::storage::cpp2::UpdateEdgeRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_chainUpdateEdge(p_req);
  });
}

void GraphStorageServiceSvIf::chainAddEdges( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::AddEdgesRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("chainAddEdges");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_chainAddEdges(const  ::nebula::storage::cpp2::AddEdgesRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { chainAddEdges(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_chainAddEdges(const  ::nebula::storage::cpp2::AddEdgesRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_chainAddEdges(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_chainAddEdges(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::AddEdgesRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_chainAddEdges(p_req);
  });
}

void GraphStorageServiceSvIf::get( ::nebula::storage::cpp2::KVGetResponse& /*_return*/, const  ::nebula::storage::cpp2::KVGetRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("get");
}

folly::SemiFuture< ::nebula::storage::cpp2::KVGetResponse> GraphStorageServiceSvIf::semifuture_get(const  ::nebula::storage::cpp2::KVGetRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::KVGetResponse& _return) { get(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::KVGetResponse> GraphStorageServiceSvIf::future_get(const  ::nebula::storage::cpp2::KVGetRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_get(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_get(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::KVGetResponse>> callback, const  ::nebula::storage::cpp2::KVGetRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_get(p_req);
  });
}

void GraphStorageServiceSvIf::put( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::KVPutRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("put");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_put(const  ::nebula::storage::cpp2::KVPutRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { put(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_put(const  ::nebula::storage::cpp2::KVPutRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_put(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_put(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::KVPutRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_put(p_req);
  });
}

void GraphStorageServiceSvIf::remove( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::KVRemoveRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("remove");
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::semifuture_remove(const  ::nebula::storage::cpp2::KVRemoveRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::ExecResponse& _return) { remove(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> GraphStorageServiceSvIf::future_remove(const  ::nebula::storage::cpp2::KVRemoveRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_remove(p_req), std::move(ka));
}

void GraphStorageServiceSvIf::async_tm_remove(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::ExecResponse>> callback, const  ::nebula::storage::cpp2::KVRemoveRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_remove(p_req);
  });
}

void GraphStorageServiceSvNull::getNeighbors( ::nebula::storage::cpp2::GetNeighborsResponse& /*_return*/, const  ::nebula::storage::cpp2::GetNeighborsRequest& /*req*/) {}

void GraphStorageServiceSvNull::getProps( ::nebula::storage::cpp2::GetPropResponse& /*_return*/, const  ::nebula::storage::cpp2::GetPropRequest& /*req*/) {}

void GraphStorageServiceSvNull::addVertices( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::AddVerticesRequest& /*req*/) {}

void GraphStorageServiceSvNull::addEdges( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::AddEdgesRequest& /*req*/) {}

void GraphStorageServiceSvNull::deleteEdges( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::DeleteEdgesRequest& /*req*/) {}

void GraphStorageServiceSvNull::deleteVertices( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::DeleteVerticesRequest& /*req*/) {}

void GraphStorageServiceSvNull::deleteTags( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::DeleteTagsRequest& /*req*/) {}

void GraphStorageServiceSvNull::updateVertex( ::nebula::storage::cpp2::UpdateResponse& /*_return*/, const  ::nebula::storage::cpp2::UpdateVertexRequest& /*req*/) {}

void GraphStorageServiceSvNull::updateEdge( ::nebula::storage::cpp2::UpdateResponse& /*_return*/, const  ::nebula::storage::cpp2::UpdateEdgeRequest& /*req*/) {}

void GraphStorageServiceSvNull::scanVertex( ::nebula::storage::cpp2::ScanResponse& /*_return*/, const  ::nebula::storage::cpp2::ScanVertexRequest& /*req*/) {}

void GraphStorageServiceSvNull::scanEdge( ::nebula::storage::cpp2::ScanResponse& /*_return*/, const  ::nebula::storage::cpp2::ScanEdgeRequest& /*req*/) {}

void GraphStorageServiceSvNull::getUUID( ::nebula::storage::cpp2::GetUUIDResp& /*_return*/, const  ::nebula::storage::cpp2::GetUUIDReq& /*req*/) {}

void GraphStorageServiceSvNull::lookupIndex( ::nebula::storage::cpp2::LookupIndexResp& /*_return*/, const  ::nebula::storage::cpp2::LookupIndexRequest& /*req*/) {}

void GraphStorageServiceSvNull::lookupAndTraverse( ::nebula::storage::cpp2::GetNeighborsResponse& /*_return*/, const  ::nebula::storage::cpp2::LookupAndTraverseRequest& /*req*/) {}

void GraphStorageServiceSvNull::chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& /*_return*/, const  ::nebula::storage::cpp2::UpdateEdgeRequest& /*req*/) {}

void GraphStorageServiceSvNull::chainAddEdges( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::AddEdgesRequest& /*req*/) {}

void GraphStorageServiceSvNull::get( ::nebula::storage::cpp2::KVGetResponse& /*_return*/, const  ::nebula::storage::cpp2::KVGetRequest& /*req*/) {}

void GraphStorageServiceSvNull::put( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::KVPutRequest& /*req*/) {}

void GraphStorageServiceSvNull::remove( ::nebula::storage::cpp2::ExecResponse& /*_return*/, const  ::nebula::storage::cpp2::KVRemoveRequest& /*req*/) {}



const char* GraphStorageServiceAsyncProcessor::getServiceName() {
  return "GraphStorageService";
}

void GraphStorageServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<GraphStorageServiceSvIf>::gen(*response.metadata_ref(), *response.context_ref());
}

void GraphStorageServiceAsyncProcessor::processSerializedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

std::shared_ptr<folly::RequestContext> GraphStorageServiceAsyncProcessor::getBaseContextForRequest() {
  return iface_->getBaseContextForRequest();
}

const GraphStorageServiceAsyncProcessor::ProcessMap& GraphStorageServiceAsyncProcessor::getBinaryProtocolProcessMap() {
  return binaryProcessMap_;
}

const GraphStorageServiceAsyncProcessor::ProcessMap GraphStorageServiceAsyncProcessor::binaryProcessMap_ {
  {"getNeighbors", &GraphStorageServiceAsyncProcessor::setUpAndProcess_getNeighbors<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"getProps", &GraphStorageServiceAsyncProcessor::setUpAndProcess_getProps<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"addVertices", &GraphStorageServiceAsyncProcessor::setUpAndProcess_addVertices<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"addEdges", &GraphStorageServiceAsyncProcessor::setUpAndProcess_addEdges<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"deleteEdges", &GraphStorageServiceAsyncProcessor::setUpAndProcess_deleteEdges<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"deleteVertices", &GraphStorageServiceAsyncProcessor::setUpAndProcess_deleteVertices<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"deleteTags", &GraphStorageServiceAsyncProcessor::setUpAndProcess_deleteTags<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"updateVertex", &GraphStorageServiceAsyncProcessor::setUpAndProcess_updateVertex<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"updateEdge", &GraphStorageServiceAsyncProcessor::setUpAndProcess_updateEdge<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"scanVertex", &GraphStorageServiceAsyncProcessor::setUpAndProcess_scanVertex<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"scanEdge", &GraphStorageServiceAsyncProcessor::setUpAndProcess_scanEdge<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"getUUID", &GraphStorageServiceAsyncProcessor::setUpAndProcess_getUUID<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"lookupIndex", &GraphStorageServiceAsyncProcessor::setUpAndProcess_lookupIndex<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"lookupAndTraverse", &GraphStorageServiceAsyncProcessor::setUpAndProcess_lookupAndTraverse<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"chainUpdateEdge", &GraphStorageServiceAsyncProcessor::setUpAndProcess_chainUpdateEdge<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"chainAddEdges", &GraphStorageServiceAsyncProcessor::setUpAndProcess_chainAddEdges<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"get", &GraphStorageServiceAsyncProcessor::setUpAndProcess_get<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"put", &GraphStorageServiceAsyncProcessor::setUpAndProcess_put<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"remove", &GraphStorageServiceAsyncProcessor::setUpAndProcess_remove<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const GraphStorageServiceAsyncProcessor::ProcessMap& GraphStorageServiceAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const GraphStorageServiceAsyncProcessor::ProcessMap GraphStorageServiceAsyncProcessor::compactProcessMap_ {
  {"getNeighbors", &GraphStorageServiceAsyncProcessor::setUpAndProcess_getNeighbors<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"getProps", &GraphStorageServiceAsyncProcessor::setUpAndProcess_getProps<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"addVertices", &GraphStorageServiceAsyncProcessor::setUpAndProcess_addVertices<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"addEdges", &GraphStorageServiceAsyncProcessor::setUpAndProcess_addEdges<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"deleteEdges", &GraphStorageServiceAsyncProcessor::setUpAndProcess_deleteEdges<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"deleteVertices", &GraphStorageServiceAsyncProcessor::setUpAndProcess_deleteVertices<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"deleteTags", &GraphStorageServiceAsyncProcessor::setUpAndProcess_deleteTags<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"updateVertex", &GraphStorageServiceAsyncProcessor::setUpAndProcess_updateVertex<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"updateEdge", &GraphStorageServiceAsyncProcessor::setUpAndProcess_updateEdge<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"scanVertex", &GraphStorageServiceAsyncProcessor::setUpAndProcess_scanVertex<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"scanEdge", &GraphStorageServiceAsyncProcessor::setUpAndProcess_scanEdge<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"getUUID", &GraphStorageServiceAsyncProcessor::setUpAndProcess_getUUID<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"lookupIndex", &GraphStorageServiceAsyncProcessor::setUpAndProcess_lookupIndex<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"lookupAndTraverse", &GraphStorageServiceAsyncProcessor::setUpAndProcess_lookupAndTraverse<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"chainUpdateEdge", &GraphStorageServiceAsyncProcessor::setUpAndProcess_chainUpdateEdge<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"chainAddEdges", &GraphStorageServiceAsyncProcessor::setUpAndProcess_chainAddEdges<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"get", &GraphStorageServiceAsyncProcessor::setUpAndProcess_get<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"put", &GraphStorageServiceAsyncProcessor::setUpAndProcess_put<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"remove", &GraphStorageServiceAsyncProcessor::setUpAndProcess_remove<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

}}} // nebula::storage::cpp2
