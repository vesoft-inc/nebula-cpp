# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

nebula_add_test(
    NAME
        connection_test
    SOURCES
        ConnectionTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

file(COPY ${CMAKE_SOURCE_DIR}/certs/test.ca.pem
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/certs/test.2.crt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

nebula_add_test(
    NAME
        connection_ssl_test
    SOURCES
        ConnectionSSLTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        session_test
    SOURCES
        SessionTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_executable(
    NAME
        regist_host
    SOURCES
        RegistHost.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        session_ssl_test
    SOURCES
        SessionSSLTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        address_test
    SOURCES
        AddressTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        config_test
    SOURCES
        ConfigTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        timezone_conversion_test
    SOURCES
        TimezoneConversionTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        session_pool_test
    SOURCES
        SessionPoolTest.cpp
    OBJECTS
        ${NEBULA_CLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)
