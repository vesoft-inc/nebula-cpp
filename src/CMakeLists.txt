# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

set(NEBULA_CLIENT_OBJS
    $<TARGET_OBJECTS:common_thrift_obj>
    $<TARGET_OBJECTS:graph_thrift_obj>
)

set(NEBULA_CLIENT_SOURCES
    client/Connection.cpp
    client/Init.cpp
    client/ConnectionPool.cpp
    client/Session.cpp
    client/SSLConfig.cpp
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
