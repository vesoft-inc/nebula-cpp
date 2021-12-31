/**
 * Autogenerated by Thrift for storage.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#include "InternalStorageServiceAsyncClient.h"

#include <thrift/lib/cpp2/gen/client_cpp.h>

namespace nebula { namespace storage { namespace cpp2 {
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, ::apache::thrift::type_class::structure,  ::nebula::storage::cpp2::ChainAddEdgesRequest*>> InternalStorageService_chainAddEdges_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, ::apache::thrift::type_class::structure,  ::nebula::storage::cpp2::ExecResponse*>> InternalStorageService_chainAddEdges_presult;
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, ::apache::thrift::type_class::structure,  ::nebula::storage::cpp2::ChainUpdateEdgeRequest*>> InternalStorageService_chainUpdateEdge_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, ::apache::thrift::type_class::structure,  ::nebula::storage::cpp2::UpdateResponse*>> InternalStorageService_chainUpdateEdge_presult;
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, ::apache::thrift::type_class::structure,  ::nebula::storage::cpp2::ChainDeleteEdgesRequest*>> InternalStorageService_chainDeleteEdges_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, ::apache::thrift::type_class::structure,  ::nebula::storage::cpp2::ExecResponse*>> InternalStorageService_chainDeleteEdges_presult;

template <typename Protocol_>
void InternalStorageServiceAsyncClient::chainAddEdgesT(Protocol_* prot, apache::thrift::RpcOptions rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {

  std::shared_ptr<apache::thrift::transport::THeader> header(ctx, &ctx->header);
  InternalStorageService_chainAddEdges_pargs args;
  args.get<0>().value = const_cast< ::nebula::storage::cpp2::ChainAddEdgesRequest*>(&p_req);
  auto sizer = [&](Protocol_* p) { return args.serializedSizeZC(p); };
  auto writer = [&](Protocol_* p) { args.write(p); };
  static constexpr const folly::StringPiece methodName = "chainAddEdges";
  apache::thrift::clientSendT<apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, Protocol_>(prot, std::move(rpcOptions), std::move(callback), ctx->ctx, std::move(header), channel_.get(), apache::thrift::ManagedStringView(methodName, false), writer, sizer);
  ctx->reqContext.setRequestHeader(nullptr);
}

template <typename Protocol_>
void InternalStorageServiceAsyncClient::chainUpdateEdgeT(Protocol_* prot, apache::thrift::RpcOptions rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {

  std::shared_ptr<apache::thrift::transport::THeader> header(ctx, &ctx->header);
  InternalStorageService_chainUpdateEdge_pargs args;
  args.get<0>().value = const_cast< ::nebula::storage::cpp2::ChainUpdateEdgeRequest*>(&p_req);
  auto sizer = [&](Protocol_* p) { return args.serializedSizeZC(p); };
  auto writer = [&](Protocol_* p) { args.write(p); };
  static constexpr const folly::StringPiece methodName = "chainUpdateEdge";
  apache::thrift::clientSendT<apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, Protocol_>(prot, std::move(rpcOptions), std::move(callback), ctx->ctx, std::move(header), channel_.get(), apache::thrift::ManagedStringView(methodName, false), writer, sizer);
  ctx->reqContext.setRequestHeader(nullptr);
}

template <typename Protocol_>
void InternalStorageServiceAsyncClient::chainDeleteEdgesT(Protocol_* prot, apache::thrift::RpcOptions rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {

  std::shared_ptr<apache::thrift::transport::THeader> header(ctx, &ctx->header);
  InternalStorageService_chainDeleteEdges_pargs args;
  args.get<0>().value = const_cast< ::nebula::storage::cpp2::ChainDeleteEdgesRequest*>(&p_req);
  auto sizer = [&](Protocol_* p) { return args.serializedSizeZC(p); };
  auto writer = [&](Protocol_* p) { args.write(p); };
  static constexpr const folly::StringPiece methodName = "chainDeleteEdges";
  apache::thrift::clientSendT<apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, Protocol_>(prot, std::move(rpcOptions), std::move(callback), ctx->ctx, std::move(header), channel_.get(), apache::thrift::ManagedStringView(methodName, false), writer, sizer);
  ctx->reqContext.setRequestHeader(nullptr);
}



void InternalStorageServiceAsyncClient::chainAddEdges(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  chainAddEdges(rpcOptions, std::move(callback), p_req);
}

void InternalStorageServiceAsyncClient::chainAddEdges(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  auto ctx = chainAddEdgesCtx(&rpcOptions);
  apache::thrift::RequestCallback::Context callbackContext;
  callbackContext.protocolId =
      apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  callbackContext.ctx = std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx);
  auto wrappedCallback = apache::thrift::toRequestClientCallbackPtr(std::move(callback), std::move(callbackContext));
  chainAddEdgesImpl(rpcOptions, std::move(ctx), std::move(wrappedCallback), p_req);
}

void InternalStorageServiceAsyncClient::chainAddEdgesImpl(const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  switch (apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      chainAddEdgesT(&writer, rpcOptions, std::move(ctx), std::move(callback), p_req);
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      chainAddEdgesT(&writer, rpcOptions, std::move(ctx), std::move(callback), p_req);
      break;
    }
    default:
    {
      apache::thrift::detail::ac::throw_app_exn("Could not find Protocol");
    }
  }
}

std::shared_ptr<::apache::thrift::detail::ac::ClientRequestContext> InternalStorageServiceAsyncClient::chainAddEdgesCtx(apache::thrift::RpcOptions* rpcOptions) {
  return std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(
      channel_->getProtocolId(),
      rpcOptions ? rpcOptions->releaseWriteHeaders() : std::map<std::string, std::string>{},
      handlers_,
      getServiceName(),
      "InternalStorageService.chainAddEdges");
}

void InternalStorageServiceAsyncClient::sync_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  sync_chainAddEdges(rpcOptions, _return, p_req);
}

void InternalStorageServiceAsyncClient::sync_chainAddEdges(apache::thrift::RpcOptions& rpcOptions,  ::nebula::storage::cpp2::ExecResponse& _return, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  apache::thrift::ClientReceiveState returnState;
  apache::thrift::ClientSyncCallback<false> callback(&returnState);
  auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  auto evb = apache::thrift::GeneratedAsyncClient::getChannel()->getEventBase();
  auto ctx = chainAddEdgesCtx(&rpcOptions);
  auto wrappedCallback = apache::thrift::RequestClientCallback::Ptr(&callback);
  chainAddEdgesImpl(rpcOptions, ctx, std::move(wrappedCallback), p_req);
  callback.waitUntilDone(evb);

  if (returnState.isException()) {
    returnState.exception().throw_exception();
  }
  returnState.resetProtocolId(protocolId);
  returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
  SCOPE_EXIT {
    if (returnState.header() && !returnState.header()->getHeaders().empty()) {
      rpcOptions.setReadHeaders(returnState.header()->releaseHeaders());
    }
  };
  return folly::fibers::runInMainContext([&] {
      recv_chainAddEdges(_return, returnState);
  });
}


folly::Future< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::future_chainAddEdges(const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  return future_chainAddEdges(rpcOptions, p_req);
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::semifuture_chainAddEdges(const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  return semifuture_chainAddEdges(rpcOptions, p_req);
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::future_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  folly::Promise< ::nebula::storage::cpp2::ExecResponse> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::FutureCallback< ::nebula::storage::cpp2::ExecResponse>>(std::move(promise), recv_wrapped_chainAddEdges, channel_);
  chainAddEdges(rpcOptions, std::move(callback), p_req);
  return future;
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::semifuture_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  auto callbackAndFuture = makeSemiFutureCallback(recv_wrapped_chainAddEdges, channel_);
  auto callback = std::move(callbackAndFuture.first);
  chainAddEdges(rpcOptions, std::move(callback), p_req);
  return std::move(callbackAndFuture.second);
}

folly::Future<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> InternalStorageServiceAsyncClient::header_future_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  folly::Promise<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::HeaderFutureCallback< ::nebula::storage::cpp2::ExecResponse>>(std::move(promise), recv_wrapped_chainAddEdges, channel_);
  chainAddEdges(rpcOptions, std::move(callback), p_req);
  return future;
}

folly::SemiFuture<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> InternalStorageServiceAsyncClient::header_semifuture_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  auto callbackAndFuture = makeHeaderSemiFutureCallback(recv_wrapped_chainAddEdges, channel_);
  auto callback = std::move(callbackAndFuture.first);
  chainAddEdges(rpcOptions, std::move(callback), p_req);
  return std::move(callbackAndFuture.second);
}

void InternalStorageServiceAsyncClient::chainAddEdges(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
  chainAddEdges(std::make_unique<apache::thrift::FunctionReplyCallback>(std::move(callback)), p_req);
}

#if FOLLY_HAS_COROUTINES
#endif // FOLLY_HAS_COROUTINES
folly::exception_wrapper InternalStorageServiceAsyncClient::recv_wrapped_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return std::move(state.exception());
  }
  if (!state.buf()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }

  using result = InternalStorageService_chainAddEdges_presult;
  constexpr auto const fname = "chainAddEdges";
  switch (state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

void InternalStorageServiceAsyncClient::recv_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  auto ew = recv_wrapped_chainAddEdges(_return, state);
  if (ew) {
    ew.throw_exception();
  }
}

void InternalStorageServiceAsyncClient::recv_instance_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_chainAddEdges(_return, state);
}

folly::exception_wrapper InternalStorageServiceAsyncClient::recv_instance_wrapped_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_chainAddEdges(_return, state);
}

void InternalStorageServiceAsyncClient::chainUpdateEdge(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  chainUpdateEdge(rpcOptions, std::move(callback), p_req);
}

void InternalStorageServiceAsyncClient::chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  auto ctx = chainUpdateEdgeCtx(&rpcOptions);
  apache::thrift::RequestCallback::Context callbackContext;
  callbackContext.protocolId =
      apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  callbackContext.ctx = std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx);
  auto wrappedCallback = apache::thrift::toRequestClientCallbackPtr(std::move(callback), std::move(callbackContext));
  chainUpdateEdgeImpl(rpcOptions, std::move(ctx), std::move(wrappedCallback), p_req);
}

void InternalStorageServiceAsyncClient::chainUpdateEdgeImpl(const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  switch (apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      chainUpdateEdgeT(&writer, rpcOptions, std::move(ctx), std::move(callback), p_req);
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      chainUpdateEdgeT(&writer, rpcOptions, std::move(ctx), std::move(callback), p_req);
      break;
    }
    default:
    {
      apache::thrift::detail::ac::throw_app_exn("Could not find Protocol");
    }
  }
}

std::shared_ptr<::apache::thrift::detail::ac::ClientRequestContext> InternalStorageServiceAsyncClient::chainUpdateEdgeCtx(apache::thrift::RpcOptions* rpcOptions) {
  return std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(
      channel_->getProtocolId(),
      rpcOptions ? rpcOptions->releaseWriteHeaders() : std::map<std::string, std::string>{},
      handlers_,
      getServiceName(),
      "InternalStorageService.chainUpdateEdge");
}

void InternalStorageServiceAsyncClient::sync_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  sync_chainUpdateEdge(rpcOptions, _return, p_req);
}

void InternalStorageServiceAsyncClient::sync_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions,  ::nebula::storage::cpp2::UpdateResponse& _return, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  apache::thrift::ClientReceiveState returnState;
  apache::thrift::ClientSyncCallback<false> callback(&returnState);
  auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  auto evb = apache::thrift::GeneratedAsyncClient::getChannel()->getEventBase();
  auto ctx = chainUpdateEdgeCtx(&rpcOptions);
  auto wrappedCallback = apache::thrift::RequestClientCallback::Ptr(&callback);
  chainUpdateEdgeImpl(rpcOptions, ctx, std::move(wrappedCallback), p_req);
  callback.waitUntilDone(evb);

  if (returnState.isException()) {
    returnState.exception().throw_exception();
  }
  returnState.resetProtocolId(protocolId);
  returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
  SCOPE_EXIT {
    if (returnState.header() && !returnState.header()->getHeaders().empty()) {
      rpcOptions.setReadHeaders(returnState.header()->releaseHeaders());
    }
  };
  return folly::fibers::runInMainContext([&] {
      recv_chainUpdateEdge(_return, returnState);
  });
}


folly::Future< ::nebula::storage::cpp2::UpdateResponse> InternalStorageServiceAsyncClient::future_chainUpdateEdge(const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  return future_chainUpdateEdge(rpcOptions, p_req);
}

folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> InternalStorageServiceAsyncClient::semifuture_chainUpdateEdge(const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  return semifuture_chainUpdateEdge(rpcOptions, p_req);
}

folly::Future< ::nebula::storage::cpp2::UpdateResponse> InternalStorageServiceAsyncClient::future_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  folly::Promise< ::nebula::storage::cpp2::UpdateResponse> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::FutureCallback< ::nebula::storage::cpp2::UpdateResponse>>(std::move(promise), recv_wrapped_chainUpdateEdge, channel_);
  chainUpdateEdge(rpcOptions, std::move(callback), p_req);
  return future;
}

folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> InternalStorageServiceAsyncClient::semifuture_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  auto callbackAndFuture = makeSemiFutureCallback(recv_wrapped_chainUpdateEdge, channel_);
  auto callback = std::move(callbackAndFuture.first);
  chainUpdateEdge(rpcOptions, std::move(callback), p_req);
  return std::move(callbackAndFuture.second);
}

folly::Future<std::pair< ::nebula::storage::cpp2::UpdateResponse, std::unique_ptr<apache::thrift::transport::THeader>>> InternalStorageServiceAsyncClient::header_future_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  folly::Promise<std::pair< ::nebula::storage::cpp2::UpdateResponse, std::unique_ptr<apache::thrift::transport::THeader>>> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::HeaderFutureCallback< ::nebula::storage::cpp2::UpdateResponse>>(std::move(promise), recv_wrapped_chainUpdateEdge, channel_);
  chainUpdateEdge(rpcOptions, std::move(callback), p_req);
  return future;
}

folly::SemiFuture<std::pair< ::nebula::storage::cpp2::UpdateResponse, std::unique_ptr<apache::thrift::transport::THeader>>> InternalStorageServiceAsyncClient::header_semifuture_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  auto callbackAndFuture = makeHeaderSemiFutureCallback(recv_wrapped_chainUpdateEdge, channel_);
  auto callback = std::move(callbackAndFuture.first);
  chainUpdateEdge(rpcOptions, std::move(callback), p_req);
  return std::move(callbackAndFuture.second);
}

void InternalStorageServiceAsyncClient::chainUpdateEdge(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
  chainUpdateEdge(std::make_unique<apache::thrift::FunctionReplyCallback>(std::move(callback)), p_req);
}

#if FOLLY_HAS_COROUTINES
#endif // FOLLY_HAS_COROUTINES
folly::exception_wrapper InternalStorageServiceAsyncClient::recv_wrapped_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return std::move(state.exception());
  }
  if (!state.buf()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }

  using result = InternalStorageService_chainUpdateEdge_presult;
  constexpr auto const fname = "chainUpdateEdge";
  switch (state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

void InternalStorageServiceAsyncClient::recv_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  auto ew = recv_wrapped_chainUpdateEdge(_return, state);
  if (ew) {
    ew.throw_exception();
  }
}

void InternalStorageServiceAsyncClient::recv_instance_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_chainUpdateEdge(_return, state);
}

folly::exception_wrapper InternalStorageServiceAsyncClient::recv_instance_wrapped_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_chainUpdateEdge(_return, state);
}

void InternalStorageServiceAsyncClient::chainDeleteEdges(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  chainDeleteEdges(rpcOptions, std::move(callback), p_req);
}

void InternalStorageServiceAsyncClient::chainDeleteEdges(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  auto ctx = chainDeleteEdgesCtx(&rpcOptions);
  apache::thrift::RequestCallback::Context callbackContext;
  callbackContext.protocolId =
      apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  callbackContext.ctx = std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx);
  auto wrappedCallback = apache::thrift::toRequestClientCallbackPtr(std::move(callback), std::move(callbackContext));
  chainDeleteEdgesImpl(rpcOptions, std::move(ctx), std::move(wrappedCallback), p_req);
}

void InternalStorageServiceAsyncClient::chainDeleteEdgesImpl(const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  switch (apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      chainDeleteEdgesT(&writer, rpcOptions, std::move(ctx), std::move(callback), p_req);
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      chainDeleteEdgesT(&writer, rpcOptions, std::move(ctx), std::move(callback), p_req);
      break;
    }
    default:
    {
      apache::thrift::detail::ac::throw_app_exn("Could not find Protocol");
    }
  }
}

std::shared_ptr<::apache::thrift::detail::ac::ClientRequestContext> InternalStorageServiceAsyncClient::chainDeleteEdgesCtx(apache::thrift::RpcOptions* rpcOptions) {
  return std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(
      channel_->getProtocolId(),
      rpcOptions ? rpcOptions->releaseWriteHeaders() : std::map<std::string, std::string>{},
      handlers_,
      getServiceName(),
      "InternalStorageService.chainDeleteEdges");
}

void InternalStorageServiceAsyncClient::sync_chainDeleteEdges( ::nebula::storage::cpp2::ExecResponse& _return, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  sync_chainDeleteEdges(rpcOptions, _return, p_req);
}

void InternalStorageServiceAsyncClient::sync_chainDeleteEdges(apache::thrift::RpcOptions& rpcOptions,  ::nebula::storage::cpp2::ExecResponse& _return, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  apache::thrift::ClientReceiveState returnState;
  apache::thrift::ClientSyncCallback<false> callback(&returnState);
  auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  auto evb = apache::thrift::GeneratedAsyncClient::getChannel()->getEventBase();
  auto ctx = chainDeleteEdgesCtx(&rpcOptions);
  auto wrappedCallback = apache::thrift::RequestClientCallback::Ptr(&callback);
  chainDeleteEdgesImpl(rpcOptions, ctx, std::move(wrappedCallback), p_req);
  callback.waitUntilDone(evb);

  if (returnState.isException()) {
    returnState.exception().throw_exception();
  }
  returnState.resetProtocolId(protocolId);
  returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
  SCOPE_EXIT {
    if (returnState.header() && !returnState.header()->getHeaders().empty()) {
      rpcOptions.setReadHeaders(returnState.header()->releaseHeaders());
    }
  };
  return folly::fibers::runInMainContext([&] {
      recv_chainDeleteEdges(_return, returnState);
  });
}


folly::Future< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::future_chainDeleteEdges(const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  return future_chainDeleteEdges(rpcOptions, p_req);
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::semifuture_chainDeleteEdges(const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  ::apache::thrift::RpcOptions rpcOptions;
  return semifuture_chainDeleteEdges(rpcOptions, p_req);
}

folly::Future< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::future_chainDeleteEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  folly::Promise< ::nebula::storage::cpp2::ExecResponse> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::FutureCallback< ::nebula::storage::cpp2::ExecResponse>>(std::move(promise), recv_wrapped_chainDeleteEdges, channel_);
  chainDeleteEdges(rpcOptions, std::move(callback), p_req);
  return future;
}

folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> InternalStorageServiceAsyncClient::semifuture_chainDeleteEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  auto callbackAndFuture = makeSemiFutureCallback(recv_wrapped_chainDeleteEdges, channel_);
  auto callback = std::move(callbackAndFuture.first);
  chainDeleteEdges(rpcOptions, std::move(callback), p_req);
  return std::move(callbackAndFuture.second);
}

folly::Future<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> InternalStorageServiceAsyncClient::header_future_chainDeleteEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  folly::Promise<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::HeaderFutureCallback< ::nebula::storage::cpp2::ExecResponse>>(std::move(promise), recv_wrapped_chainDeleteEdges, channel_);
  chainDeleteEdges(rpcOptions, std::move(callback), p_req);
  return future;
}

folly::SemiFuture<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> InternalStorageServiceAsyncClient::header_semifuture_chainDeleteEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  auto callbackAndFuture = makeHeaderSemiFutureCallback(recv_wrapped_chainDeleteEdges, channel_);
  auto callback = std::move(callbackAndFuture.first);
  chainDeleteEdges(rpcOptions, std::move(callback), p_req);
  return std::move(callbackAndFuture.second);
}

void InternalStorageServiceAsyncClient::chainDeleteEdges(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::nebula::storage::cpp2::ChainDeleteEdgesRequest& p_req) {
  chainDeleteEdges(std::make_unique<apache::thrift::FunctionReplyCallback>(std::move(callback)), p_req);
}

#if FOLLY_HAS_COROUTINES
#endif // FOLLY_HAS_COROUTINES
folly::exception_wrapper InternalStorageServiceAsyncClient::recv_wrapped_chainDeleteEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return std::move(state.exception());
  }
  if (!state.buf()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }

  using result = InternalStorageService_chainDeleteEdges_presult;
  constexpr auto const fname = "chainDeleteEdges";
  switch (state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state, _return);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

void InternalStorageServiceAsyncClient::recv_chainDeleteEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  auto ew = recv_wrapped_chainDeleteEdges(_return, state);
  if (ew) {
    ew.throw_exception();
  }
}

void InternalStorageServiceAsyncClient::recv_instance_chainDeleteEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_chainDeleteEdges(_return, state);
}

folly::exception_wrapper InternalStorageServiceAsyncClient::recv_instance_wrapped_chainDeleteEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_chainDeleteEdges(_return, state);
}


}}} // nebula::storage::cpp2
