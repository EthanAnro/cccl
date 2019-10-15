//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/unordered_map>
// UNSUPPORTED: c++98, c++03, c++11, c++14
// UNSUPPORTED: libcpp-no-deduction-guides
// XFAIL: clang-6, apple-clang-9.0, apple-clang-9.1, apple-clang-10.0.0

// template<class InputIterator,
//          class Hash = hash<iter-key-type<InputIterator>>,
//          class Pred = equal_to<iter-key-type<InputIterator>>,
//          class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
// unordered_map(InputIterator, InputIterator, typename see below::size_type = see below,
//               Hash = Hash(), Pred = Pred(), Allocator = Allocator())
//   -> unordered_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash, Pred,
//                    Allocator>;
//
// template<class Key, class T, class Hash = hash<Key>,
//          class Pred = equal_to<Key>, class Allocator = allocator<pair<const Key, T>>>
// unordered_map(initializer_list<pair<Key, T>>,
//               typename see below::size_type = see below, Hash = Hash(),
//               Pred = Pred(), Allocator = Allocator())
//   -> unordered_map<Key, T, Hash, Pred, Allocator>;
//
// template<class InputIterator, class Allocator>
// unordered_map(InputIterator, InputIterator, typename see below::size_type, Allocator)
//   -> unordered_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
//                    hash<iter-key-type<InputIterator>>,
//                    equal_to<iter-key-type<InputIterator>>, Allocator>;
//
// template<class InputIterator, class Allocator>
// unordered_map(InputIterator, InputIterator, Allocator)
//   -> unordered_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
//                    hash<iter-key-type<InputIterator>>,
//                    equal_to<iter-key-type<InputIterator>>, Allocator>;
//
// template<class InputIterator, class Hash, class Allocator>
// unordered_map(InputIterator, InputIterator, typename see below::size_type, Hash, Allocator)
//   -> unordered_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash,
//                    equal_to<iter-key-type<InputIterator>>, Allocator>;
//
// template<class Key, class T, class Allocator>
// unordered_map(initializer_list<pair<Key, T>>, typename see below::size_type, Allocator)
//   -> unordered_map<Key, T, hash<Key>, equal_to<Key>, Allocator>;
//
// template<class Key, class T, class Allocator>
// unordered_map(initializer_list<pair<Key, T>>, Allocator)
//   -> unordered_map<Key, T, hash<Key>, equal_to<Key>, Allocator>;
//
// template<class Key, class T, class Hash, class Allocator>
// unordered_map(initializer_list<pair<Key, T>>, typename see below::size_type, Hash,
//               Allocator)
//   -> unordered_map<Key, T, Hash, equal_to<Key>, Allocator>;

#include <cuda/std/functional>
#include <cuda/std/unordered_map>

int main(int, char**)
{
    using P = cuda::std::pair<const int, int>;
    {
        // cannot deduce Key from nothing
        cuda::std::unordered_map m; // expected-error{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Size)
        cuda::std::unordered_map m(42); // expected-error{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Size, Hash)
        cuda::std::unordered_map m(42, cuda::std::hash<int>());
            // expected-error@-1{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Size, Hash, Pred)
        cuda::std::unordered_map m(42, cuda::std::hash<int>(), cuda::std::equal_to<int>());
            // expected-error@-1{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Size, Hash, Pred, Allocator)
        cuda::std::unordered_map m(42, cuda::std::hash<int>(), cuda::std::equal_to<int>(), cuda::std::allocator<P>());
            // expected-error@-1{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Allocator)
        cuda::std::unordered_map m(cuda::std::allocator<P>{});
            // expected-error@-1{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Size, Allocator)
        cuda::std::unordered_map m(42, cuda::std::allocator<P>());
            // expected-error@-1{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }
    {
        // cannot deduce Key from just (Size, Hash, Allocator)
        cuda::std::unordered_map m(42, cuda::std::hash<int>(), cuda::std::allocator<P>());
            // expected-error@-1{{no viable constructor or deduction guide for deduction of template arguments of 'unordered_map'}}
    }

  return 0;
}
