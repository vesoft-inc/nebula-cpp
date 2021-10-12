/**
 * Autogenerated by Thrift for graph.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "GraphService.h"
#include "GraphService.tcc"
#include "graph_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace nebula { namespace graph { namespace cpp2 {
std::unique_ptr<apache::thrift::AsyncProcessor> GraphServiceSvIf::getProcessor() {
  return std::make_unique<GraphServiceAsyncProcessor>(this);
}


void GraphServiceSvIf::authenticate(nebula::AuthResponse& /*_return*/, const ::std::string& /*username*/, const ::std::string& /*password*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("authenticate");
}

folly::SemiFuture<nebula::AuthResponse> GraphServiceSvIf::semifuture_authenticate(const ::std::string& p_username, const ::std::string& p_password) {
  return apache::thrift::detail::si::semifuture_returning([&](nebula::AuthResponse& _return) { authenticate(_return, p_username, p_password); });
}

folly::Future<nebula::AuthResponse> GraphServiceSvIf::future_authenticate(const ::std::string& p_username, const ::std::string& p_password) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_authenticate(p_username, p_password), std::move(ka));
}

void GraphServiceSvIf::async_tm_authenticate(std::unique_ptr<apache::thrift::HandlerCallback<nebula::AuthResponse>> callback, const ::std::string& p_username, const ::std::string& p_password) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_authenticate(p_username, p_password);
  });
}

void GraphServiceSvIf::signout(int64_t /*sessionId*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("signout");
}

folly::SemiFuture<folly::Unit> GraphServiceSvIf::semifuture_signout(int64_t p_sessionId) {
  return apache::thrift::detail::si::semifuture([&] {
    return signout(p_sessionId);
  });
}

folly::Future<folly::Unit> GraphServiceSvIf::future_signout(int64_t p_sessionId) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_signout(p_sessionId), std::move(ka));
}

void GraphServiceSvIf::async_tm_signout(std::unique_ptr<apache::thrift::HandlerCallbackBase> callback, int64_t p_sessionId) {
  apache::thrift::detail::si::async_tm_oneway(this, std::move(callback), [&] {
    return future_signout(p_sessionId);
  });
}

void GraphServiceSvIf::execute(nebula::ExecutionResponse& /*_return*/, int64_t /*sessionId*/, const ::std::string& /*stmt*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("execute");
}

folly::SemiFuture<nebula::ExecutionResponse> GraphServiceSvIf::semifuture_execute(int64_t p_sessionId, const ::std::string& p_stmt) {
  return apache::thrift::detail::si::semifuture_returning([&](nebula::ExecutionResponse& _return) { execute(_return, p_sessionId, p_stmt); });
}

folly::Future<nebula::ExecutionResponse> GraphServiceSvIf::future_execute(int64_t p_sessionId, const ::std::string& p_stmt) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_execute(p_sessionId, p_stmt), std::move(ka));
}

void GraphServiceSvIf::async_tm_execute(std::unique_ptr<apache::thrift::HandlerCallback<nebula::ExecutionResponse>> callback, int64_t p_sessionId, const ::std::string& p_stmt) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_execute(p_sessionId, p_stmt);
  });
}

void GraphServiceSvIf::executeJson(::std::string& /*_return*/, int64_t /*sessionId*/, const ::std::string& /*stmt*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("executeJson");
}

folly::SemiFuture<::std::string> GraphServiceSvIf::semifuture_executeJson(int64_t p_sessionId, const ::std::string& p_stmt) {
  return apache::thrift::detail::si::semifuture_returning([&](::std::string& _return) { executeJson(_return, p_sessionId, p_stmt); });
}

folly::Future<::std::string> GraphServiceSvIf::future_executeJson(int64_t p_sessionId, const ::std::string& p_stmt) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_executeJson(p_sessionId, p_stmt), std::move(ka));
}

void GraphServiceSvIf::async_tm_executeJson(std::unique_ptr<apache::thrift::HandlerCallback<::std::string>> callback, int64_t p_sessionId, const ::std::string& p_stmt) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_executeJson(p_sessionId, p_stmt);
  });
}

void GraphServiceSvIf::verifyClientVersion( ::nebula::graph::cpp2::VerifyClientVersionResp& /*_return*/, const  ::nebula::graph::cpp2::VerifyClientVersionReq& /*req*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("verifyClientVersion");
}

folly::SemiFuture< ::nebula::graph::cpp2::VerifyClientVersionResp> GraphServiceSvIf::semifuture_verifyClientVersion(const  ::nebula::graph::cpp2::VerifyClientVersionReq& p_req) {
  return apache::thrift::detail::si::semifuture_returning([&]( ::nebula::graph::cpp2::VerifyClientVersionResp& _return) { verifyClientVersion(_return, p_req); });
}

folly::Future< ::nebula::graph::cpp2::VerifyClientVersionResp> GraphServiceSvIf::future_verifyClientVersion(const  ::nebula::graph::cpp2::VerifyClientVersionReq& p_req) {
  using Source = apache::thrift::concurrency::ThreadManager::Source;
  auto scope = getRequestContext()->getRequestExecutionScope();
  auto ka = getThreadManager()->getKeepAlive(std::move(scope), Source::INTERNAL);
  return apache::thrift::detail::si::future(semifuture_verifyClientVersion(p_req), std::move(ka));
}

void GraphServiceSvIf::async_tm_verifyClientVersion(std::unique_ptr<apache::thrift::HandlerCallback< ::nebula::graph::cpp2::VerifyClientVersionResp>> callback, const  ::nebula::graph::cpp2::VerifyClientVersionReq& p_req) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_verifyClientVersion(p_req);
  });
}

void GraphServiceSvNull::authenticate(nebula::AuthResponse& /*_return*/, const ::std::string& /*username*/, const ::std::string& /*password*/) {}

void GraphServiceSvNull::signout(int64_t /*sessionId*/) {
  return;
}

void GraphServiceSvNull::execute(nebula::ExecutionResponse& /*_return*/, int64_t /*sessionId*/, const ::std::string& /*stmt*/) {}

void GraphServiceSvNull::executeJson(::std::string& /*_return*/, int64_t /*sessionId*/, const ::std::string& /*stmt*/) {}

void GraphServiceSvNull::verifyClientVersion( ::nebula::graph::cpp2::VerifyClientVersionResp& /*_return*/, const  ::nebula::graph::cpp2::VerifyClientVersionReq& /*req*/) {}



const char* GraphServiceAsyncProcessor::getServiceName() {
  return "GraphService";
}

void GraphServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<GraphServiceSvIf>::gen(*response.metadata_ref(), *response.context_ref());
}

void GraphServiceAsyncProcessor::processSerializedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

std::shared_ptr<folly::RequestContext> GraphServiceAsyncProcessor::getBaseContextForRequest() {
  return iface_->getBaseContextForRequest();
}

const GraphServiceAsyncProcessor::ProcessMap& GraphServiceAsyncProcessor::getBinaryProtocolProcessMap() {
  return binaryProcessMap_;
}

const GraphServiceAsyncProcessor::ProcessMap GraphServiceAsyncProcessor::binaryProcessMap_ {
  {"authenticate", &GraphServiceAsyncProcessor::setUpAndProcess_authenticate<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"signout", &GraphServiceAsyncProcessor::setUpAndProcess_signout<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"execute", &GraphServiceAsyncProcessor::setUpAndProcess_execute<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"executeJson", &GraphServiceAsyncProcessor::setUpAndProcess_executeJson<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"verifyClientVersion", &GraphServiceAsyncProcessor::setUpAndProcess_verifyClientVersion<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const GraphServiceAsyncProcessor::ProcessMap& GraphServiceAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const GraphServiceAsyncProcessor::ProcessMap GraphServiceAsyncProcessor::compactProcessMap_ {
  {"authenticate", &GraphServiceAsyncProcessor::setUpAndProcess_authenticate<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"signout", &GraphServiceAsyncProcessor::setUpAndProcess_signout<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"execute", &GraphServiceAsyncProcessor::setUpAndProcess_execute<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"executeJson", &GraphServiceAsyncProcessor::setUpAndProcess_executeJson<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"verifyClientVersion", &GraphServiceAsyncProcessor::setUpAndProcess_verifyClientVersion<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

}}} // nebula::graph::cpp2
