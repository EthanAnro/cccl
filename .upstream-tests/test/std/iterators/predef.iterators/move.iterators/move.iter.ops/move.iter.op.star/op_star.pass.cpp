//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/iterator>

// move_iterator

// reference operator*() const;
//
//  constexpr in C++17

#include <cuda/std/iterator>
#include <cuda/std/cassert>
#include <cuda/std/memory>

#include "test_macros.h"

class A
{
    int data_;
public:
    A() : data_(1) {}
    ~A() {data_ = -1;}

    friend bool operator==(const A& x, const A& y)
        {return x.data_ == y.data_;}
};

template <class It>
void
test(It i, typename cuda::std::iterator_traits<It>::value_type x)
{
    cuda::std::move_iterator<It> r(i);
    assert(*r == x);
    typename cuda::std::iterator_traits<It>::value_type x2 = *r;
    assert(x2 == x);
}

struct do_nothing
{
    void operator()(void*) const {}
};


int main(int, char**)
{
    {
        A a;
        test(&a, A());
    }
#if TEST_STD_VER >= 11
    {
        int i;
        cuda::std::unique_ptr<int, do_nothing> p(&i);
        test(&p, cuda::std::unique_ptr<int, do_nothing>(&i));
    }
#endif
#if TEST_STD_VER > 14
    {
    constexpr const char *p = "123456789";
    typedef cuda::std::move_iterator<const char *> MI;
    constexpr MI it1 = cuda::std::make_move_iterator(p);
    constexpr MI it2 = cuda::std::make_move_iterator(p+1);
    static_assert(*it1 == p[0], "");
    static_assert(*it2 == p[1], "");
    }
#endif

  return 0;
}
