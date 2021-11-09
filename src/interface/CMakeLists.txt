# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

foreach(mod "common" "graph")
    set(${mod}-cpp2-HEADERS
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_constants.h
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_data.h
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_types.h
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_types_custom_protocol.h
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_types.tcc
    )

    set(${mod}-cpp2-SOURCES
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_constants.cpp
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_data.cpp
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_metadata.cpp
    ${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/${mod}_types.cpp
    )
endforeach()

set(graph-cpp2-HEADERS
${graph-cpp2-HEADERS}
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphService.h
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphService.tcc
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphServiceAsyncClient.h
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphService_custom_protocol.h
)
set(graph-cpp2-SOURCES
${graph-cpp2-SOURCES}
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphService.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphServiceAsyncClient.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphService_processmap_binary.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphService_processmap_compact.cpp
)

add_compile_options(-fPIC)

add_library(
  "common_thrift_obj"
  OBJECT
  ${common-cpp2-SOURCES}
)

add_library(
  "graph_thrift_obj"
  OBJECT
  ${graph-cpp2-SOURCES}
)
