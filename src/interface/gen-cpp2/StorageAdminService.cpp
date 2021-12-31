/**
 * Autogenerated by Thrift for storage.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "StorageAdminService.h"
#include "StorageAdminService.tcc"
#include "storage_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace nebula { namespace storage { namespace cpp2 {
std::unique_ptr<apache::thrift::AsyncProcessor> StorageAdminServiceSvIf::getProcessor() {
  return std::make_unique<StorageAdminServiceAsyncProcessor>(this);
}


void StorageAdminServiceSvIf::transLeader( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::TransLeaderReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("transLeader");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_transLeader(const  ::nebula::storage::cpp2::TransLeaderReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { transLeader(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_transLeader(const  ::nebula::storage::cpp2::TransLeaderReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_transLeader(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_transLeader(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::TransLeaderReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_transLeader(p_req);
  });
}

void StorageAdminServiceSvIf::addPart( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::AddPartReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("addPart");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_addPart(const  ::nebula::storage::cpp2::AddPartReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { addPart(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_addPart(const  ::nebula::storage::cpp2::AddPartReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_addPart(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_addPart(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::AddPartReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_addPart(p_req);
  });
}

void StorageAdminServiceSvIf::addLearner( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::AddLearnerReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("addLearner");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_addLearner(const  ::nebula::storage::cpp2::AddLearnerReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { addLearner(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_addLearner(const  ::nebula::storage::cpp2::AddLearnerReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_addLearner(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_addLearner(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::AddLearnerReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_addLearner(p_req);
  });
}

void StorageAdminServiceSvIf::removePart( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::RemovePartReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("removePart");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_removePart(const  ::nebula::storage::cpp2::RemovePartReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { removePart(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_removePart(const  ::nebula::storage::cpp2::RemovePartReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_removePart(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_removePart(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::RemovePartReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_removePart(p_req);
  });
}

void StorageAdminServiceSvIf::memberChange( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::MemberChangeReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("memberChange");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_memberChange(const  ::nebula::storage::cpp2::MemberChangeReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { memberChange(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_memberChange(const  ::nebula::storage::cpp2::MemberChangeReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_memberChange(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_memberChange(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::MemberChangeReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_memberChange(p_req);
  });
}

void StorageAdminServiceSvIf::waitingForCatchUpData( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::CatchUpDataReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("waitingForCatchUpData");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_waitingForCatchUpData(const  ::nebula::storage::cpp2::CatchUpDataReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { waitingForCatchUpData(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_waitingForCatchUpData(const  ::nebula::storage::cpp2::CatchUpDataReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_waitingForCatchUpData(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_waitingForCatchUpData(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::CatchUpDataReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_waitingForCatchUpData(p_req);
  });
}

void StorageAdminServiceSvIf::createCheckpoint( ::nebula::storage::cpp2::CreateCPResp& /*_return*/, const  ::nebula::storage::cpp2::CreateCPRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("createCheckpoint");
}

folly::SemiFuture< ::nebula::storage::cpp2::CreateCPResp> StorageAdminServiceSvIf::semifuture_createCheckpoint(const  ::nebula::storage::cpp2::CreateCPRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::CreateCPResp& _return) { createCheckpoint(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::CreateCPResp> StorageAdminServiceSvIf::future_createCheckpoint(const  ::nebula::storage::cpp2::CreateCPRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_createCheckpoint(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_createCheckpoint(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::CreateCPResp>> callback, const  ::nebula::storage::cpp2::CreateCPRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_createCheckpoint(p_req);
  });
}

void StorageAdminServiceSvIf::dropCheckpoint( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::DropCPRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("dropCheckpoint");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_dropCheckpoint(const  ::nebula::storage::cpp2::DropCPRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { dropCheckpoint(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_dropCheckpoint(const  ::nebula::storage::cpp2::DropCPRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_dropCheckpoint(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_dropCheckpoint(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::DropCPRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_dropCheckpoint(p_req);
  });
}

void StorageAdminServiceSvIf::blockingWrites( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::BlockingSignRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("blockingWrites");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_blockingWrites(const  ::nebula::storage::cpp2::BlockingSignRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { blockingWrites(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_blockingWrites(const  ::nebula::storage::cpp2::BlockingSignRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_blockingWrites(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_blockingWrites(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::BlockingSignRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_blockingWrites(p_req);
  });
}

void StorageAdminServiceSvIf::rebuildTagIndex( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::RebuildIndexRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("rebuildTagIndex");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_rebuildTagIndex(const  ::nebula::storage::cpp2::RebuildIndexRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { rebuildTagIndex(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_rebuildTagIndex(const  ::nebula::storage::cpp2::RebuildIndexRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_rebuildTagIndex(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_rebuildTagIndex(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::RebuildIndexRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_rebuildTagIndex(p_req);
  });
}

void StorageAdminServiceSvIf::rebuildEdgeIndex( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::RebuildIndexRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("rebuildEdgeIndex");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_rebuildEdgeIndex(const  ::nebula::storage::cpp2::RebuildIndexRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { rebuildEdgeIndex(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_rebuildEdgeIndex(const  ::nebula::storage::cpp2::RebuildIndexRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_rebuildEdgeIndex(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_rebuildEdgeIndex(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::RebuildIndexRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_rebuildEdgeIndex(p_req);
  });
}

void StorageAdminServiceSvIf::getLeaderParts( ::nebula::storage::cpp2::GetLeaderPartsResp& /*_return*/, const  ::nebula::storage::cpp2::GetLeaderReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getLeaderParts");
}

folly::SemiFuture< ::nebula::storage::cpp2::GetLeaderPartsResp> StorageAdminServiceSvIf::semifuture_getLeaderParts(const  ::nebula::storage::cpp2::GetLeaderReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::GetLeaderPartsResp& _return) { getLeaderParts(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::GetLeaderPartsResp> StorageAdminServiceSvIf::future_getLeaderParts(const  ::nebula::storage::cpp2::GetLeaderReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_getLeaderParts(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_getLeaderParts(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::GetLeaderPartsResp>> callback, const  ::nebula::storage::cpp2::GetLeaderReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_getLeaderParts(p_req);
  });
}

void StorageAdminServiceSvIf::checkPeers( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::CheckPeersReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("checkPeers");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_checkPeers(const  ::nebula::storage::cpp2::CheckPeersReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { checkPeers(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_checkPeers(const  ::nebula::storage::cpp2::CheckPeersReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_checkPeers(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_checkPeers(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::CheckPeersReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_checkPeers(p_req);
  });
}

void StorageAdminServiceSvIf::addAdminTask( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::AddAdminTaskRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("addAdminTask");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_addAdminTask(const  ::nebula::storage::cpp2::AddAdminTaskRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { addAdminTask(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_addAdminTask(const  ::nebula::storage::cpp2::AddAdminTaskRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_addAdminTask(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_addAdminTask(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::AddAdminTaskRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_addAdminTask(p_req);
  });
}

void StorageAdminServiceSvIf::stopAdminTask( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::StopAdminTaskRequest& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("stopAdminTask");
}

folly::SemiFuture< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::semifuture_stopAdminTask(const  ::nebula::storage::cpp2::StopAdminTaskRequest& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::storage::cpp2::AdminExecResp& _return) { stopAdminTask(_return, p_req); });
}

folly::Future< ::nebula::storage::cpp2::AdminExecResp> StorageAdminServiceSvIf::future_stopAdminTask(const  ::nebula::storage::cpp2::StopAdminTaskRequest& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_stopAdminTask(p_req), std::move(ka));
}

void StorageAdminServiceSvIf::async_tm_stopAdminTask(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::storage::cpp2::AdminExecResp>> callback, const  ::nebula::storage::cpp2::StopAdminTaskRequest& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_stopAdminTask(p_req);
  });
}

void StorageAdminServiceSvNull::transLeader( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::TransLeaderReq& /*req*/) {}

void StorageAdminServiceSvNull::addPart( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::AddPartReq& /*req*/) {}

void StorageAdminServiceSvNull::addLearner( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::AddLearnerReq& /*req*/) {}

void StorageAdminServiceSvNull::removePart( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::RemovePartReq& /*req*/) {}

void StorageAdminServiceSvNull::memberChange( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::MemberChangeReq& /*req*/) {}

void StorageAdminServiceSvNull::waitingForCatchUpData( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::CatchUpDataReq& /*req*/) {}

void StorageAdminServiceSvNull::createCheckpoint( ::nebula::storage::cpp2::CreateCPResp& /*_return*/, const  ::nebula::storage::cpp2::CreateCPRequest& /*req*/) {}

void StorageAdminServiceSvNull::dropCheckpoint( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::DropCPRequest& /*req*/) {}

void StorageAdminServiceSvNull::blockingWrites( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::BlockingSignRequest& /*req*/) {}

void StorageAdminServiceSvNull::rebuildTagIndex( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::RebuildIndexRequest& /*req*/) {}

void StorageAdminServiceSvNull::rebuildEdgeIndex( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::RebuildIndexRequest& /*req*/) {}

void StorageAdminServiceSvNull::getLeaderParts( ::nebula::storage::cpp2::GetLeaderPartsResp& /*_return*/, const  ::nebula::storage::cpp2::GetLeaderReq& /*req*/) {}

void StorageAdminServiceSvNull::checkPeers( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::CheckPeersReq& /*req*/) {}

void StorageAdminServiceSvNull::addAdminTask( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::AddAdminTaskRequest& /*req*/) {}

void StorageAdminServiceSvNull::stopAdminTask( ::nebula::storage::cpp2::AdminExecResp& /*_return*/, const  ::nebula::storage::cpp2::StopAdminTaskRequest& /*req*/) {}



const char* StorageAdminServiceAsyncProcessor::getServiceName() {
  return "StorageAdminService";
}

void StorageAdminServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<StorageAdminServiceSvIf>::gen(*response.metadata_ref(), *response.context_ref());
}

void StorageAdminServiceAsyncProcessor::processSerializedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

std::shared_ptr<folly::RequestContext> StorageAdminServiceAsyncProcessor::getBaseContextForRequest() {
  return iface_->getBaseContextForRequest();
}

const StorageAdminServiceAsyncProcessor::ProcessMap& StorageAdminServiceAsyncProcessor::getBinaryProtocolProcessMap() {
  return binaryProcessMap_;
}

const StorageAdminServiceAsyncProcessor::ProcessMap StorageAdminServiceAsyncProcessor::binaryProcessMap_ {
  {"transLeader", &StorageAdminServiceAsyncProcessor::setUpAndProcess_transLeader<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"addPart", &StorageAdminServiceAsyncProcessor::setUpAndProcess_addPart<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"addLearner", &StorageAdminServiceAsyncProcessor::setUpAndProcess_addLearner<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"removePart", &StorageAdminServiceAsyncProcessor::setUpAndProcess_removePart<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"memberChange", &StorageAdminServiceAsyncProcessor::setUpAndProcess_memberChange<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"waitingForCatchUpData", &StorageAdminServiceAsyncProcessor::setUpAndProcess_waitingForCatchUpData<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"createCheckpoint", &StorageAdminServiceAsyncProcessor::setUpAndProcess_createCheckpoint<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"dropCheckpoint", &StorageAdminServiceAsyncProcessor::setUpAndProcess_dropCheckpoint<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"blockingWrites", &StorageAdminServiceAsyncProcessor::setUpAndProcess_blockingWrites<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"rebuildTagIndex", &StorageAdminServiceAsyncProcessor::setUpAndProcess_rebuildTagIndex<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"rebuildEdgeIndex", &StorageAdminServiceAsyncProcessor::setUpAndProcess_rebuildEdgeIndex<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"getLeaderParts", &StorageAdminServiceAsyncProcessor::setUpAndProcess_getLeaderParts<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"checkPeers", &StorageAdminServiceAsyncProcessor::setUpAndProcess_checkPeers<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"addAdminTask", &StorageAdminServiceAsyncProcessor::setUpAndProcess_addAdminTask<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"stopAdminTask", &StorageAdminServiceAsyncProcessor::setUpAndProcess_stopAdminTask<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const StorageAdminServiceAsyncProcessor::ProcessMap& StorageAdminServiceAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const StorageAdminServiceAsyncProcessor::ProcessMap StorageAdminServiceAsyncProcessor::compactProcessMap_ {
  {"transLeader", &StorageAdminServiceAsyncProcessor::setUpAndProcess_transLeader<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"addPart", &StorageAdminServiceAsyncProcessor::setUpAndProcess_addPart<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"addLearner", &StorageAdminServiceAsyncProcessor::setUpAndProcess_addLearner<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"removePart", &StorageAdminServiceAsyncProcessor::setUpAndProcess_removePart<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"memberChange", &StorageAdminServiceAsyncProcessor::setUpAndProcess_memberChange<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"waitingForCatchUpData", &StorageAdminServiceAsyncProcessor::setUpAndProcess_waitingForCatchUpData<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"createCheckpoint", &StorageAdminServiceAsyncProcessor::setUpAndProcess_createCheckpoint<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"dropCheckpoint", &StorageAdminServiceAsyncProcessor::setUpAndProcess_dropCheckpoint<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"blockingWrites", &StorageAdminServiceAsyncProcessor::setUpAndProcess_blockingWrites<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"rebuildTagIndex", &StorageAdminServiceAsyncProcessor::setUpAndProcess_rebuildTagIndex<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"rebuildEdgeIndex", &StorageAdminServiceAsyncProcessor::setUpAndProcess_rebuildEdgeIndex<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"getLeaderParts", &StorageAdminServiceAsyncProcessor::setUpAndProcess_getLeaderParts<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"checkPeers", &StorageAdminServiceAsyncProcessor::setUpAndProcess_checkPeers<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"addAdminTask", &StorageAdminServiceAsyncProcessor::setUpAndProcess_addAdminTask<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"stopAdminTask", &StorageAdminServiceAsyncProcessor::setUpAndProcess_stopAdminTask<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

}}} // nebula::storage::cpp2
