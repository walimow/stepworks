//
// Created by kh on 01.12.20.
//

#include "box/wrekurs.hpp"
#include "util/singular.hpp"
#include <gtest/gtest.h>
#include <vector>

using stepworks::iterativ_continuation;
using stepworks::singular::singular_t;

template <typename Ty>
struct  sum_s{
  using return_t=Ty;
  auto operator()( const Ty& a,  const Ty&& b)const ->Ty{
        return a + std::move(b);
    }
};



TEST (continuation_test, forward){

    std::vector<int> vi{1,2,3,4,5};
    auto x = iterativ_continuation( sum_s<int>{}, vi);
    EXPECT_EQ(x,15);

}

template <typename Ty>
struct  sum_singul{
    using return_t=Ty;
    auto operator()(const Ty& a,  const singular_t< Ty>&& b)const ->singular_t< Ty>{
        return a + std::move(b._value);
    }
};



TEST (continuation_test, forward_singular){

    std::vector<int> vi{1,2,3,4,5};
    auto x = iterativ_continuation( sum_singul<int>{}, vi);
    EXPECT_EQ(x._value,15);

}




