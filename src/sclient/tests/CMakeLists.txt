# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

nebula_add_test(
    NAME
        storage_client_test
    SOURCES
        StorageClientTest.cpp
    OBJECTS
        ${NEBULA_SCLIENT_OBJS}
        $<TARGET_OBJECTS:nebula_storage_client_obj>
    LIBRARIES
        gtest
        ${NEBULA_CLIENT_LIBRARIES}
)
