//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11, c++14, c++17

// <cuda/std/functional>
//
// reference_wrapper
//
// template <ObjectType T> reference_wrapper<T> ref(T& t);
//
//  where T is an incomplete type (since C++20)

#include <cuda/std/functional>
#include <cuda/std/cassert>

#include "test_macros.h"


struct Foo;

Foo& get_foo();

void test() {
    Foo& foo = get_foo();
    cuda::std::reference_wrapper<Foo> ref = cuda::std::ref(foo);
    assert(&ref.get() == &foo);
}

struct Foo { };

Foo& get_foo() {
    static Foo foo;
    return foo;
}

int main() {
    test();
}
