//
// Created by kh on 01.12.20.
//


#include <detect//detect_iterable.hpp>
#include <gtest/gtest.h>

using stepworks::detect::is_forward_iterable;


TEST ( detect_forward_iterable, testint )
{
    auto n = is_forward_iterable< int>::value ;
    EXPECT_FALSE(n);
}

TEST ( detect_iterable, testvectorint )
{
    auto y = is_forward_iterable< std::vector<int>>::value ;
    EXPECT_TRUE(y);
}