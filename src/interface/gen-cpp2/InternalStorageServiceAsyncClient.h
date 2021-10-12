/**
 * Autogenerated by Thrift for storage.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/client_h.h>

#include "storage_types.h"
#include "common_types.h"
#include "meta_types.h"

namespace apache { namespace thrift {
  class Cpp2RequestContext;
  namespace detail { namespace ac { struct ClientRequestContext; }}
  namespace transport { class THeader; }
}}

namespace nebula { namespace storage { namespace cpp2 {

class InternalStorageServiceAsyncClient : public apache::thrift::GeneratedAsyncClient {
 public:
  using apache::thrift::GeneratedAsyncClient::GeneratedAsyncClient;

  char const* getServiceName() const noexcept override {
    return "InternalStorageService";
  }


  virtual void chainAddEdges(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual void chainAddEdges(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
 protected:
  void chainAddEdgesImpl(const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
 public:

  virtual void sync_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual void sync_chainAddEdges(apache::thrift::RpcOptions& rpcOptions,  ::nebula::storage::cpp2::ExecResponse& _return, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);

  virtual folly::Future< ::nebula::storage::cpp2::ExecResponse> future_chainAddEdges(const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> semifuture_chainAddEdges(const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual folly::Future< ::nebula::storage::cpp2::ExecResponse> future_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual folly::SemiFuture< ::nebula::storage::cpp2::ExecResponse> semifuture_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual folly::Future<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> header_future_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  virtual folly::SemiFuture<std::pair< ::nebula::storage::cpp2::ExecResponse, std::unique_ptr<apache::thrift::transport::THeader>>> header_semifuture_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);

#if FOLLY_HAS_COROUTINES
  template <int = 0>
  folly::coro::Task< ::nebula::storage::cpp2::ExecResponse> co_chainAddEdges(const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
    return co_chainAddEdges<false>(nullptr, p_req);
  }
  template <int = 0>
  folly::coro::Task< ::nebula::storage::cpp2::ExecResponse> co_chainAddEdges(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
    return co_chainAddEdges<true>(&rpcOptions, p_req);
  }
 private:
  template <bool hasRpcOptions>
  folly::coro::Task< ::nebula::storage::cpp2::ExecResponse> co_chainAddEdges(apache::thrift::RpcOptions* rpcOptions, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req) {
    const folly::CancellationToken& cancelToken =
        co_await folly::coro::co_current_cancellation_token;
    const bool cancellable = cancelToken.canBeCancelled();
    apache::thrift::ClientReceiveState returnState;
    apache::thrift::ClientSyncCallback<false> callback(&returnState);
    auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
    auto ctx = chainAddEdgesCtx(rpcOptions);
    using CancellableCallback = apache::thrift::CancellableRequestClientCallback<false>;
    auto cancellableCallback = cancellable ? CancellableCallback::create(&callback, channel_) : nullptr;
    static const apache::thrift::RpcOptions defaultRpcOptions;
    auto wrappedCallback = apache::thrift::RequestClientCallback::Ptr(cancellableCallback ? (apache::thrift::RequestClientCallback*)cancellableCallback.get() : &callback);
    if constexpr (hasRpcOptions) {
      chainAddEdgesImpl(*rpcOptions, ctx, std::move(wrappedCallback), p_req);
    } else {
      chainAddEdgesImpl(defaultRpcOptions, ctx, std::move(wrappedCallback), p_req);
    }
    if (cancellable) {
      folly::CancellationCallback cb(cancelToken, [&] { CancellableCallback::cancel(std::move(cancellableCallback)); });
      co_await callback.co_waitUntilDone();
    } else {
      co_await callback.co_waitUntilDone();
    }
    if (returnState.isException()) {
      co_yield folly::coro::co_error(std::move(returnState.exception()));
    }
    returnState.resetProtocolId(protocolId);
    returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
    SCOPE_EXIT {
      if (hasRpcOptions && returnState.header() && !returnState.header()->getHeaders().empty()) {
        rpcOptions->setReadHeaders(returnState.header()->releaseHeaders());
      }
    };
     ::nebula::storage::cpp2::ExecResponse _return;
    if (auto ew = recv_wrapped_chainAddEdges(_return, returnState)) {
      co_yield folly::coro::co_error(std::move(ew));
    }
    co_return _return;
  }
 public:
#endif // FOLLY_HAS_COROUTINES

  virtual void chainAddEdges(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);


  static folly::exception_wrapper recv_wrapped_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state);
  static void recv_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state);
  // Mock friendly virtual instance method
  virtual void recv_instance_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state);
  virtual folly::exception_wrapper recv_instance_wrapped_chainAddEdges( ::nebula::storage::cpp2::ExecResponse& _return, ::apache::thrift::ClientReceiveState& state);
 private:
  template <typename Protocol_>
  void chainAddEdgesT(Protocol_* prot, apache::thrift::RpcOptions rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainAddEdgesRequest& p_req);
  std::shared_ptr<::apache::thrift::detail::ac::ClientRequestContext> chainAddEdgesCtx(apache::thrift::RpcOptions* rpcOptions);
 public:
  virtual void chainUpdateEdge(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual void chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
 protected:
  void chainUpdateEdgeImpl(const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
 public:

  virtual void sync_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual void sync_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions,  ::nebula::storage::cpp2::UpdateResponse& _return, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);

  virtual folly::Future< ::nebula::storage::cpp2::UpdateResponse> future_chainUpdateEdge(const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> semifuture_chainUpdateEdge(const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual folly::Future< ::nebula::storage::cpp2::UpdateResponse> future_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual folly::SemiFuture< ::nebula::storage::cpp2::UpdateResponse> semifuture_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual folly::Future<std::pair< ::nebula::storage::cpp2::UpdateResponse, std::unique_ptr<apache::thrift::transport::THeader>>> header_future_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  virtual folly::SemiFuture<std::pair< ::nebula::storage::cpp2::UpdateResponse, std::unique_ptr<apache::thrift::transport::THeader>>> header_semifuture_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);

#if FOLLY_HAS_COROUTINES
  template <int = 0>
  folly::coro::Task< ::nebula::storage::cpp2::UpdateResponse> co_chainUpdateEdge(const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
    return co_chainUpdateEdge<false>(nullptr, p_req);
  }
  template <int = 0>
  folly::coro::Task< ::nebula::storage::cpp2::UpdateResponse> co_chainUpdateEdge(apache::thrift::RpcOptions& rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
    return co_chainUpdateEdge<true>(&rpcOptions, p_req);
  }
 private:
  template <bool hasRpcOptions>
  folly::coro::Task< ::nebula::storage::cpp2::UpdateResponse> co_chainUpdateEdge(apache::thrift::RpcOptions* rpcOptions, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req) {
    const folly::CancellationToken& cancelToken =
        co_await folly::coro::co_current_cancellation_token;
    const bool cancellable = cancelToken.canBeCancelled();
    apache::thrift::ClientReceiveState returnState;
    apache::thrift::ClientSyncCallback<false> callback(&returnState);
    auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
    auto ctx = chainUpdateEdgeCtx(rpcOptions);
    using CancellableCallback = apache::thrift::CancellableRequestClientCallback<false>;
    auto cancellableCallback = cancellable ? CancellableCallback::create(&callback, channel_) : nullptr;
    static const apache::thrift::RpcOptions defaultRpcOptions;
    auto wrappedCallback = apache::thrift::RequestClientCallback::Ptr(cancellableCallback ? (apache::thrift::RequestClientCallback*)cancellableCallback.get() : &callback);
    if constexpr (hasRpcOptions) {
      chainUpdateEdgeImpl(*rpcOptions, ctx, std::move(wrappedCallback), p_req);
    } else {
      chainUpdateEdgeImpl(defaultRpcOptions, ctx, std::move(wrappedCallback), p_req);
    }
    if (cancellable) {
      folly::CancellationCallback cb(cancelToken, [&] { CancellableCallback::cancel(std::move(cancellableCallback)); });
      co_await callback.co_waitUntilDone();
    } else {
      co_await callback.co_waitUntilDone();
    }
    if (returnState.isException()) {
      co_yield folly::coro::co_error(std::move(returnState.exception()));
    }
    returnState.resetProtocolId(protocolId);
    returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
    SCOPE_EXIT {
      if (hasRpcOptions && returnState.header() && !returnState.header()->getHeaders().empty()) {
        rpcOptions->setReadHeaders(returnState.header()->releaseHeaders());
      }
    };
     ::nebula::storage::cpp2::UpdateResponse _return;
    if (auto ew = recv_wrapped_chainUpdateEdge(_return, returnState)) {
      co_yield folly::coro::co_error(std::move(ew));
    }
    co_return _return;
  }
 public:
#endif // FOLLY_HAS_COROUTINES

  virtual void chainUpdateEdge(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);


  static folly::exception_wrapper recv_wrapped_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state);
  static void recv_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state);
  // Mock friendly virtual instance method
  virtual void recv_instance_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state);
  virtual folly::exception_wrapper recv_instance_wrapped_chainUpdateEdge( ::nebula::storage::cpp2::UpdateResponse& _return, ::apache::thrift::ClientReceiveState& state);
 private:
  template <typename Protocol_>
  void chainUpdateEdgeT(Protocol_* prot, apache::thrift::RpcOptions rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback, const  ::nebula::storage::cpp2::ChainUpdateEdgeRequest& p_req);
  std::shared_ptr<::apache::thrift::detail::ac::ClientRequestContext> chainUpdateEdgeCtx(apache::thrift::RpcOptions* rpcOptions);
 public:
};

}}} // nebula::storage::cpp2
