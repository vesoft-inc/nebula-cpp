# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

foreach(mod "common" "graph" "meta" "storage")
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

set(meta-cpp2-HEADERS
${meta-cpp2-HEADERS}
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaService.h
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaService.tcc
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaServiceAsyncClient.h
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaService_custom_protocol.h
)
set(meta-cpp2-SOURCES
${meta-cpp2-SOURCES}
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaService.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaServiceAsyncClient.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaService_processmap_binary.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/MetaService_processmap_compact.cpp
)


set(storage-cpp2-HEADERS
${storage-cpp2-HEADERS}
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageService.h
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageService.tcc
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageServiceAsyncClient.h
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageService_custom_protocol.h
)
set(storage-cpp2-SOURCES
${storage-cpp2-SOURCES}
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageService.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageServiceAsyncClient.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageService_processmap_binary.cpp
${CMAKE_SOURCE_DIR}/src/interface/gen-cpp2/GraphStorageService_processmap_compact.cpp
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

add_library(
  "meta_thrift_obj"
  OBJECT
  ${meta-cpp2-SOURCES}
)

add_library(
  "storage_thrift_obj"
  OBJECT
  ${storage-cpp2-SOURCES}
)
