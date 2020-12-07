//
// Created by kh on 23.11.20.
//

#include <detect/detect_allocator.hpp>
#include <gtest/gtest.h>

#include <array>
#include <vector>

#include <initializer_list>
#include <box/box.hpp>

using stepworks::detect::has_allocator;

TEST ( detect_alloc, testvector )
{
    auto y = has_allocator< std::vector<int>>::value ;
    EXPECT_TRUE(y);
}

TEST ( detect_alloc, testarray )
{
    auto n = has_allocator< std::array<int,42>>::value ;
    EXPECT_FALSE(n);
}

TEST ( detect_alloc, testinlist )
{
    auto n = has_allocator< std::initializer_list<int>>::value ;
    EXPECT_FALSE(n);
}

TEST ( detect_alloc, test_box_inlist )
{
    using stepworks::bxx::box;

    auto n = has_allocator< std::initializer_list<  typename box<int, std::initializer_list>::agg_t  >>::value ;
    EXPECT_FALSE(n);
}
