/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

class ClientTest : public ::testing::Test {
protected:
    static ::testing::AssertionResult verifyResultWithoutOrder(const nebula::DataSet& resp,
                                                               const nebula::DataSet& expect) {
        nebula::DataSet respCopy = resp;
        nebula::DataSet expectCopy = expect;
        std::sort(respCopy.rows.begin(), respCopy.rows.end());
        std::sort(expectCopy.rows.begin(), expectCopy.rows.end());
        if (respCopy != expectCopy) {
            return ::testing::AssertionFailure() << "Resp is : " << resp << std::endl
                                                 << "Expect : " << expect;
        }
        return ::testing::AssertionSuccess();
    }
};

