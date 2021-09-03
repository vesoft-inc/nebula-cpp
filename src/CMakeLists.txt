# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
# attached with Common Clause Condition 1.0, found in the LICENSES directory.

set(NEBULA_CLIENT_OBJS
    $<TARGET_OBJECTS:common_base_obj>
    $<TARGET_OBJECTS:common_common_thrift_obj>
    $<TARGET_OBJECTS:common_graph_thrift_obj>
    $<TARGET_OBJECTS:common_datatypes_obj>
    $<TARGET_OBJECTS:common_graph_obj>
    $<TARGET_OBJECTS:common_time_utils_obj>
)

set(NEBULA_SCLIENT_OBJS
    $<TARGET_OBJECTS:common_base_obj>
    $<TARGET_OBJECTS:common_common_thrift_obj>
    $<TARGET_OBJECTS:common_meta_thrift_obj>
    $<TARGET_OBJECTS:common_storage_thrift_obj>
    $<TARGET_OBJECTS:common_datatypes_obj>
    $<TARGET_OBJECTS:common_meta_client_obj>
    $<TARGET_OBJECTS:common_graph_storage_client_obj>
    $<TARGET_OBJECTS:common_file_based_cluster_id_man_obj>
    $<TARGET_OBJECTS:common_version_obj>
    $<TARGET_OBJECTS:common_expression_obj>
    $<TARGET_OBJECTS:common_http_client_obj>
    $<TARGET_OBJECTS:common_network_obj>
    $<TARGET_OBJECTS:common_process_obj>
    $<TARGET_OBJECTS:common_graph_thrift_obj>
    $<TARGET_OBJECTS:common_storage_client_base_obj>
    $<TARGET_OBJECTS:common_stats_obj>
    $<TARGET_OBJECTS:common_time_obj>
    $<TARGET_OBJECTS:common_thrift_obj>
    $<TARGET_OBJECTS:common_meta_obj>
    $<TARGET_OBJECTS:common_ws_obj>
    $<TARGET_OBJECTS:common_ws_common_obj>
    $<TARGET_OBJECTS:common_thread_obj>
    $<TARGET_OBJECTS:common_fs_obj>
    $<TARGET_OBJECTS:common_concurrent_obj>
    $<TARGET_OBJECTS:common_conf_obj>
    $<TARGET_OBJECTS:common_charset_obj>
    $<TARGET_OBJECTS:common_encryption_obj>
    $<TARGET_OBJECTS:common_function_manager_obj>
    $<TARGET_OBJECTS:common_agg_function_manager_obj>
    $<TARGET_OBJECTS:common_time_utils_obj>
    $<TARGET_OBJECTS:common_graph_obj>
    $<TARGET_OBJECTS:common_ft_es_graph_adapter_obj>
)

set(NEBULA_CLIENT_SOURCES
    client/Connection.cpp
    client/Init.cpp
    client/ConnectionPool.cpp
    client/Session.cpp
)

set(NEBULA_SCLIENT_SOURCES
    sclient/StorageClient.cpp
    sclient/ScanEdgeIter.cpp
    sclient/ScanVertexIter.cpp
    sclient/Init.cpp
)

set(NEBULA_LIBRARIES
    ${OPENSSL_SSL_LIBRARY}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${THRIFT_LIBRARIES}
    folly
    boost_context
    boost_system
    glog
    gflags
    snappy
    z
    zstd
    lz4
    lzma
    event
    double-conversion
    pthread
    dl
    ssl
    crypto
    bz2
    fmt
    unwind
    proxygenhttpserver
    proxygen
    wangle
    fizz
    sodium
    -static-libgcc
    -static-libstdc++
    -Wl,--no-undefined
    ${GETTIME_LIB}
    atomic
)

nebula_add_library(
    nebula_graph_client SHARED
    ${NEBULA_CLIENT_OBJS}
    ${NEBULA_CLIENT_SOURCES}
)

nebula_add_library(
    nebula_storage_client SHARED
    ${NEBULA_SCLIENT_OBJS}
    ${NEBULA_SCLIENT_SOURCES}
)

target_link_libraries(
    nebula_graph_client
    ${NEBULA_LIBRARIES}
)

target_link_libraries(
    nebula_storage_client
    ${NEBULA_LIBRARIES}
)

install(
    TARGETS nebula_graph_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    TARGETS nebula_storage_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

nebula_add_library(
    nebula_graph_client_obj OBJECT
    ${NEBULA_CLIENT_SOURCES}
)

nebula_add_library(
    nebula_storage_client_obj OBJECT
    ${NEBULA_SCLIENT_SOURCES}
)

nebula_add_subdirectory(client)
nebula_add_subdirectory(sclient)
