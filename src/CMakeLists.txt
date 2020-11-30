# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
# attached with Common Clause Condition 1.0, found in the LICENSES directory.

set(NEBULA_CLIENT_OBJS
    $<TARGET_OBJECTS:common_base_obj>
    $<TARGET_OBJECTS:common_common_thrift_obj>
    $<TARGET_OBJECTS:common_graph_thrift_obj>
    $<TARGET_OBJECTS:common_datatypes_obj>
    $<TARGET_OBJECTS:common_graph_obj>
)

set(NEBULA_CLIENT_SOURCES
    client/Connection.cpp
    client/Init.cpp
    client/ConnectionPool.cpp
    client/Session.cpp
)

set(NEBULA_CLIENT_LIBRARIES
    ${OPENSSL_SSL_LIBRARY}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${THRIFT_LIBRARIES}
    wangle
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
    bz2
    event
    double-conversion
    pthread
    dl
    ssl
    crypto
    bz2
    -static-libgcc
    -static-libstdc++
    -Wl,--no-undefined
    ${GETTIME_LIB}
)

nebula_add_library(
    nebula_graph_client SHARED
    ${NEBULA_CLIENT_OBJS}
    ${NEBULA_CLIENT_SOURCES}
)

target_link_libraries(
    nebula_graph_client
    ${NEBULA_CLIENT_LIBRARIES}
)

install(
    TARGETS nebula_graph_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

nebula_add_library(
    nebula_graph_client_obj OBJECT
    ${NEBULA_CLIENT_SOURCES}
)

nebula_add_subdirectory(client)
