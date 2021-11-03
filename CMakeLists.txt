# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
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
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/nebula)

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

set(ENABLE_PIC ON FORCE)
set(ENABLE_JEMALLOC OFF FORCE)

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

install(
    DIRECTORY include/common
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PATTERN ".gitkeep" EXCLUDE
)

add_custom_target(
  format
  COMMAND "find" "include" "src/client" "src/datatypes" "src/time" "src/graph" "-type" "f" "\\(" "-iname" "\\*.h" "-o" "-iname" "\\*.cpp" "\\)" "|" "xargs" "clang-format" "-i"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

include(CPackage)
package(ON
        "nebula-graph-client"
        "https://github.com/vesoft-inc/nebula-cpp/releases"
        ${CMAKE_SOURCE_DIR}/package)
