# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

nebula_add_test(
    NAME
        meta_client_test
    SOURCES
        MetaClientTest.cpp
    OBJECTS
        ${NEBULA_MCLIENT_OBJS}
        $<TARGET_OBJECTS:graph_thrift_obj>
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
        $<TARGET_OBJECTS:nebula_meta_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)

nebula_add_test(
    NAME
        meta_client_ssl_test
    SOURCES
        MetaClientSSLTest.cpp
    OBJECTS
        ${NEBULA_MCLIENT_OBJS}
        $<TARGET_OBJECTS:graph_thrift_obj>
        $<TARGET_OBJECTS:nebula_common_obj>
        $<TARGET_OBJECTS:nebula_graph_client_obj>
        $<TARGET_OBJECTS:nebula_meta_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_THIRD_PARTY_LIBRARIES}
)
