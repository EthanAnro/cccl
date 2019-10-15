//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/regex>
// UNSUPPORTED: libcpp-no-exceptions
// UNSUPPORTED: c++98, c++03

// the "n" and "m" in `a{n,m}` should be within the numeric limits.
// requirement "m >= n" should be checked.

#include <cuda/std/regex>
#include <cuda/std/cassert>
#include "test_macros.h"

int main(int, char**) {
  // test that `n <= m`
  for (cuda::std::regex_constants::syntax_option_type op :
       {cuda::std::regex::basic}) {
    try {
      TEST_IGNORE_NODISCARD cuda::std::regex("a\\{3,2\\}", op);
      assert(false);
    } catch (const cuda::std::regex_error &e) {
      assert(e.code() == cuda::std::regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == cuda::std::regex_constants::error_badbrace);
    }
  }
  for (cuda::std::regex_constants::syntax_option_type op :
       {cuda::std::regex::ECMAScript, cuda::std::regex::extended, cuda::std::regex::egrep,
        cuda::std::regex::awk}) {
    try {
      TEST_IGNORE_NODISCARD cuda::std::regex("a{3,2}", op);
      assert(false);
    } catch (const cuda::std::regex_error &e) {
      assert(e.code() == cuda::std::regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == cuda::std::regex_constants::error_badbrace);
    }
  }

  // test that both bounds are within the limit
  for (cuda::std::regex_constants::syntax_option_type op :
       {cuda::std::regex::basic}) {
    try {
      TEST_IGNORE_NODISCARD cuda::std::regex("a\\{100000000000000000000,10000000000000000000\\}", op);
      assert(false);
    } catch (const cuda::std::regex_error &e) {
      assert(e.code() == cuda::std::regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == cuda::std::regex_constants::error_badbrace);
    }
  }
  for (cuda::std::regex_constants::syntax_option_type op :
       {cuda::std::regex::ECMAScript, cuda::std::regex::extended, cuda::std::regex::egrep,
        cuda::std::regex::awk}) {
    try {
      TEST_IGNORE_NODISCARD cuda::std::regex("a{100000000000000000000,10000000000000000000}", op);
      assert(false);
    } catch (const cuda::std::regex_error &e) {
      assert(e.code() == cuda::std::regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == cuda::std::regex_constants::error_badbrace);
    }
  }
  return 0;
}
