# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

set(NEBULA_CLIENT_OBJS
    $<TARGET_OBJECTS:common_thrift_obj>
    $<TARGET_OBJECTS:graph_thrift_obj>
)

set(NEBULA_MCLIENT_OBJS
    $<TARGET_OBJECTS:common_thrift_obj>
    $<TARGET_OBJECTS:meta_thrift_obj>
)

set(NEBULA_SCLIENT_OBJS
    $<TARGET_OBJECTS:common_thrift_obj>
    $<TARGET_OBJECTS:meta_thrift_obj>
    $<TARGET_OBJECTS:storage_thrift_obj>
)

set(NEBULA_COMMON_SOURCES
    datatypes/Date.cpp
    datatypes/Edge.cpp
    datatypes/Geography.cpp
    datatypes/HostAddr.cpp
    datatypes/List.cpp
    datatypes/Map.cpp
    datatypes/Path.cpp
    datatypes/Set.cpp
    datatypes/Value.cpp
    datatypes/Vertex.cpp
    graph/Response.cpp
    time/TimeConversion.cpp
    geo/io/wkt/WKTWriter.cpp
    geo/io/wkb/WKBWriter.cpp
    geo/io/wkb/ByteOrderDataIOStream.cpp
    Init.cpp
)

set(NEBULA_CLIENT_SOURCES
    client/Connection.cpp
    client/ConnectionPool.cpp
    client/Session.cpp
    client/SSLConfig.cpp
)

set(NEBULA_MCLIENT_SOURCES
    mclient/MetaClient.cpp
)

set(NEBULA_SCLIENT_SOURCES
    ${NEBULA_MCLIENT_SOURCES}
    sclient/StorageClient.cpp
    sclient/ScanEdgeIter.cpp
)

set(NEBULA_THIRD_PARTY_LIBRARIES
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
    fmt
    unwind
    -static-libgcc
    -static-libstdc++
    -Wl,--no-undefined
    ${GETTIME_LIB}
    atomic
)

nebula_add_subdirectory(interface)

nebula_add_library(
    nebula_graph_client SHARED
    ${NEBULA_CLIENT_OBJS}
    ${NEBULA_CLIENT_SOURCES}
    ${NEBULA_COMMON_SOURCES}
)

nebula_add_library(
    nebula_meta_client SHARED
    ${NEBULA_MCLIENT_OBJS}
    ${NEBULA_MCLIENT_SOURCES}
    ${NEBULA_COMMON_SOURCES}
)

nebula_add_library(
    nebula_storage_client SHARED
    ${NEBULA_SCLIENT_OBJS}
    ${NEBULA_SCLIENT_SOURCES}
    ${NEBULA_COMMON_SOURCES}
)

target_link_libraries(
    nebula_graph_client
    ${NEBULA_THIRD_PARTY_LIBRARIES}
)

target_link_libraries(
    nebula_meta_client
    ${NEBULA_THIRD_PARTY_LIBRARIES}
)

target_link_libraries(
    nebula_storage_client
    ${NEBULA_THIRD_PARTY_LIBRARIES}
)

install(
    TARGETS nebula_graph_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    TARGETS nebula_meta_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    TARGETS nebula_storage_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

nebula_add_library(
    nebula_common_obj OBJECT
    ${NEBULA_COMMON_SOURCES}
)

nebula_add_library(
    nebula_graph_client_obj OBJECT
    ${NEBULA_CLIENT_SOURCES}
)

nebula_add_library(
    nebula_meta_client_obj OBJECT
    ${NEBULA_MCLIENT_SOURCES}
)

nebula_add_library(
    nebula_storage_client_obj OBJECT
    ${NEBULA_SCLIENT_SOURCES}
)

nebula_add_subdirectory(client)
nebula_add_subdirectory(sclient)
nebula_add_subdirectory(mclient)
