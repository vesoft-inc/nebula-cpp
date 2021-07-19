# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
# attached with Common Clause Condition 1.0, found in the LICENSES directory.
#
# The build can be controlled by defining following variables on the
# <cmake> command line
#
#   CMAKE_C_COMPILER                -- Specify the compiler for C language
#   CMAKE_CXX_COMPILER              -- Specify the compiler for C++ language
#
#   NEBULA_THIRDPARTY_ROOT          -- Specify the root directory for third-party
#
#   NEBULA_COMMON_REPO_URL          -- Git URL for the nebula-common repo
#   NEBULA_COMMON_REPO_TAG          -- Tag/branch of the nebula-common repo
#
#   ENABLE_TESTING                 -- Build unit test
#
# CMake version check
cmake_minimum_required(VERSION 3.5.0)

# Set the project name
project("Nebula C++ Client" C CXX)
set(PACKAGE_NAME "nebula-client")

set(CMAKE_CXX_STANDARD 11)  # specify the C++ standard

option(ENABLE_MODULE_UPDATE "Automatically update module" OFF)
option(DISABLE_CLONE_COMMON "Automatically disable clone common module" OFF)

add_definitions(-DNEBULA_HOME=${CMAKE_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Submodules
if("${NEBULA_COMMON_REPO_URL}" STREQUAL "")
    SET(NEBULA_COMMON_REPO_URL "https://github.com/vesoft-inc/nebula-common.git")
endif()

if("${NEBULA_COMMON_REPO_TAG}" STREQUAL "")
    SET(NEBULA_COMMON_REPO_TAG "master")
endif()

include(FetchModule)
if(NOT NEBULA_COMMON_SOURCE_DIR)
    if (NOT ${DISABLE_CLONE_COMMON})
        nebula_fetch_module(
            NAME
                common
            URL
                ${NEBULA_COMMON_REPO_URL}
            TAG
                ${NEBULA_COMMON_REPO_TAG}
            UPDATE
                ${ENABLE_MODULE_UPDATE}
        )
    endif()
    set(nebula_common_source_dir ${CMAKE_SOURCE_DIR}/modules/common)
    set(nebula_common_build_dir ${CMAKE_BINARY_DIR}/modules/common)
else()
    set(nebula_common_source_dir ${NEBULA_COMMON_SOURCE_DIR})
    if(NOT NEBULA_COMMON_BUILD_DIR)
        set(nebula_common_build_dir ${CMAKE_BINARY_DIR}/modules/common)
    else()
        set(nebula_common_build_dir ${NEBULA_COMMON_BUILD_DIR})
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH ${nebula_common_source_dir}/cmake)
list(APPEND CMAKE_MODULE_PATH ${nebula_common_source_dir}/cmake/nebula)

include(PlatformCheck)
include(NebulaCMakeMacros)
include(GeneralCMakeOptions)
include(ABIConfig)
include(GeneralCMakeConfig)
include(GeneralCompilerConfig)
include(LinkerConfig)
include(CcacheConfig)
include(ThirdPartyConfig)
include(SanitizerConfig)
include(GitHooksConfig)
include(GitInfoConfig)
include(NebulaCustomTargets)
include(ConfigNebulaCommon)

set(ENABLE_PIC ON FORCE)
set(ENABLE_JEMALLOC OFF FORCE)
config_nebula_common(
    SOURCE_DIR ${nebula_common_source_dir}
    BUILD_DIR ${nebula_common_build_dir}
)

add_custom_target(
    clean-modules
    DEPENDS clean-common
)

include(GNUInstallDirs)

include_directories(AFTER ${CMAKE_SOURCE_DIR}/include)

# Remove the target exporting file
file(REMOVE ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}-config.cmake)

macro(nebula_add_library name type)
    add_library(${name} ${type} ${ARGN})
    export(
        TARGETS ${name}
        NAMESPACE "client_"
        APPEND
        FILE ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}-config.cmake
    )
    add_dependencies(
        ${name}
        common_project
    )
endmacro()

nebula_add_shared_linker_flag(-static-libstdc++)
nebula_add_shared_linker_flag(-static-libgcc)
nebula_add_shared_linker_flag(-rdynamic)
nebula_add_shared_linker_flag(-Wl,--no-undefined)
nebula_add_shared_linker_flag("-Wl,--version-script=${CMAKE_SOURCE_DIR}/exported-symbols.map")


nebula_add_subdirectory(src)

install(
    DIRECTORY include/nebula
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PATTERN ".gitkeep" EXCLUDE
)

# resuse the datatypes in common
install(DIRECTORY ${nebula_common_source_dir}/src/common/datatypes
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/common
        FILES_MATCHING PATTERN "*.h")

# reuse the response of graph in common
install(DIRECTORY ${nebula_common_source_dir}/src/common/graph
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/common
        FILES_MATCHING PATTERN "*.h")

# reuse the time utils in common
install(DIRECTORY ${nebula_common_source_dir}/src/common/time
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/common
        FILES_MATCHING PATTERN "TimeConversion.h")

# reuse the thrift types in common
install(
    FILES
        ${nebula_common_source_dir}/src/common/thrift/ThriftTypes.h
    PERMISSIONS
        OWNER_WRITE OWNER_READ
        GROUP_READ
        WORLD_READ
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/common/thrift
)

include(CPackage)
package(ON
        "nebula-graph-client"
        "https://github.com/vesoft-inc/nebula-cpp/releases"
        ${CMAKE_SOURCE_DIR}/package)
