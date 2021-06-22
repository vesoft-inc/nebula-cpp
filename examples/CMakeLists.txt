# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
# attached with Common Clause Condition 1.0, found in the LICENSES directory.
#

# Set the project name
project("Nebula C++ Client simple example" C CXX)

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


# This project only depends on the nebula-client headers/library
include_directories(${NEBULA_HOME}/include)
link_directories(${NEBULA_HOME}/lib64)

add_executable(session_example
    SessionExample.cpp
)

target_link_libraries(session_example
    PRIVATE
        nebula_graph_client
)
