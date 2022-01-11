//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/iterator>

// template <InsertionContainer Cont>
//   insert_iterator<Cont>
//   inserter(Cont& x, Cont::iterator i);

#include <cuda/std/iterator>
#include <cuda/std/vector>
#include <cuda/std/cassert>
#include "nasty_containers.h"

#include "test_macros.h"

template <class C>
void
test(C c)
{
    cuda::std::insert_iterator<C> i = cuda::std::inserter(c, c.end());
    i = 0;
    assert(c.size() == 1);
    assert(c.back() == 0);
}

int main(int, char**)
{
    test(cuda::std::vector<int>());
    test(nasty_vector<int>());

  return 0;
}
