# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License,
# attached with Common Clause Condition 1.0, found in the LICENSES directory.

# TODO check the exception in CI environment
# nebula_add_test(
    # NAME
        # connection_test
    # SOURCES
        # ConnectionTest.cpp
    # OBJECTS
        # ${NEBULA_CLIENT_OBJS}
        # $<TARGET_OBJECTS:nebula_graph_client_obj>
    # LIBRARIES
        # gtest
        # ${NEBULA_CLIENT_LIBRARIES}
# )

nebula_add_test(
    NAME
        session_test
    SOURCES
        SessionTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_CLIENT_LIBRARIES}
)

nebula_add_test(
    NAME
        address_test
    SOURCES
        AddressTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_CLIENT_LIBRARIES}
)

nebula_add_test(
    NAME
        config_test
    SOURCES
        ConfigTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_CLIENT_LIBRARIES}
)

nebula_add_test(
    NAME
        timezone_conversion_test
    SOURCES
        TimezoneConversionTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_CLIENT_LIBRARIES}
)
