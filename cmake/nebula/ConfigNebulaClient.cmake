# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
#

macro(config_nebula_client)
    message(">>>> Configuring Nebula Client <<<<")
    cmake_parse_arguments(
        client
        ""
        "SOURCE_DIR;BUILD_DIR"
        ""
        ${ARGN}
    )
    set(client_source_dir ${client_SOURCE_DIR})
    set(client_build_dir ${client_BUILD_DIR})
    if(NOT EXISTS ${client_build_dir})
        file(MAKE_DIRECTORY ${client_build_dir})
    endif()

    option(DISABLE_CLONE_COMMON "Automatically disable clone common module" OFF)

    execute_process(
        COMMAND
            ${CMAKE_COMMAND}
                -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                -DNEBULA_THIRDPARTY_ROOT=${NEBULA_THIRDPARTY_ROOT}
                -DNEBULA_OTHER_ROOT=${NEBULA_OTHER_ROOT}
                -DENABLE_JEMALLOC=${ENABLE_JEMALLOC}
                -DENABLE_TESTING=OFF
                -DENABLE_CCACHE=${ENABLE_CCACHE}
                -DENABLE_ASAN=${ENABLE_ASAN}
                -DENABLE_UBSAN=${ENABLE_UBSAN}
                -DENABLE_FRAME_POINTER=${ENABLE_FRAME_POINTER}
                -DENABLE_PIC=${ENABLE_PIC}
                -DENABLE_COMPRESSED_DEBUG_INFO=${ENABLE_COMPRESSED_DEBUG_INFO}
                -DNEBULA_USE_LINKER=${NEBULA_USE_LINKER}
                -DENABLE_GDB_SCRIPT_SECTION=${ENABLE_GDB_SCRIPT_SECTION}
                -DDISABLE_CXX11_ABI=${DISABLE_CXX11_ABI}
                -DDISABLE_CLONE_COMMON=ON
                ${client_source_dir}
        WORKING_DIRECTORY ${client_build_dir}
        RESULT_VARIABLE cmake_status
    )

    if(NOT ${cmake_result} EQUAL 0)
        message(FATAL_ERROR "Failed to configure nebula-client")
    endif()

    add_custom_target(
        client_project ALL
        COMMAND +${CMAKE_COMMAND} --build ${client_build_dir}
    )

    add_custom_target(
        clean-client
        COMMAND $(MAKE) clean
        WORKING_DIRECTORY ${client_build_dir}
    )

    set(nebula-client_DIR ${client_build_dir})
    find_package(nebula-client REQUIRED)

    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BUILD_DIR}/modules/common)
    set(nebula-common_DIR ${client_build_dir}/modules/common)
    find_package(nebula-common)

    include_directories(AFTER ${client_source_dir}/include)
    include_directories(AFTER ${client_build_dir}/include)
    include_directories(AFTER ${client_source_dir}/src)
    include_directories(AFTER ${client_build_dir}/src)

    include_directories(AFTER ${client_source_dir}/modules/common/src)
    include_directories(AFTER ${client_build_dir}/modules/common/src)
    message(">>>> Configuring Nebula Client done <<<<")
endmacro()
