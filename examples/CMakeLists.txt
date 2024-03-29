# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.
#

# Set the project name
project("Nebula C++ Client simple example" C CXX)
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_STANDARD 11)  # specify the C++ standard

if (NOT NEBULA_HOME)
    set(NEBULA_HOME /usr/local/nebula)
endif()

option(DISABLE_CXX11_ABI                "Whether to disable cxx11 abi" OFF)

# Is abi 11
if (DISABLE_CXX11_ABI)
    message(STATUS "Set D_GLIBCXX_USE_CXX11_ABI to 0")
    add_compile_options(-D_GLIBCXX_USE_CXX11_ABI=0)
else()
    message(STATUS "Set D_GLIBCXX_USE_CXX11_ABI to 1")
    add_compile_options(-D_GLIBCXX_USE_CXX11_ABI=1)
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")

# This project only depends on the nebula-client headers/library
include_directories(${NEBULA_HOME}/include)
link_directories(${NEBULA_HOME}/lib64)
link_directories(${NEBULA_HOME}/lib)

add_executable(session_example
    SessionExample.cpp
)

add_executable(session_pool_example
    SessionPoolExample.cpp
)

add_executable(storage_client_example
    StorageClientExample.cpp
)

target_link_libraries(session_example
    PRIVATE
        nebula_graph_client
        -pthread
)

target_link_libraries(session_pool_example
    PRIVATE
        nebula_graph_client
        -pthread
)

target_link_libraries(storage_client_example
    PRIVATE
        nebula_storage_client
        -pthread
)
