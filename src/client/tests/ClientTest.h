/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 */

#pragma once

#include <gtest/gtest.h>
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

  static ::testing::AssertionResult verifyResultWithoutOrder(const nebula::ExecutionResponse& resp,
                                                             const nebula::DataSet& expect) {
    auto result = succeeded(resp);
    if (!result) {
      return result;
    }
    const auto& data = *resp.data;
    return verifyResultWithoutOrder(data, expect);
  }

  static ::testing::AssertionResult succeeded(const nebula::ExecutionResponse& resp) {
    if (resp.errorCode != nebula::ErrorCode::SUCCEEDED) {
      return ::testing::AssertionFailure()
             << "Execution Failed with error: " << resp.errorCode << "," << *resp.errorMsg;
    }
    return ::testing::AssertionSuccess();
  }
};
