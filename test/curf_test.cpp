#include "gtest/gtest.h"
#include <eal/curf.hpp>

#include <functional>
#include <util/ignore.hpp>

struct a_times_b_minus_c {
    int operator()(int a, int b, int c) {
        return a*b-c;
    }
};

TEST (curf_test_case, curf_abc)
{
    auto  f27 = stepworks::eal::curf::bind(  a_times_b_minus_c(), 10, 2, 3 )();
    EXPECT_EQ ( f27, 17);
}

TEST (curf_test_case, curf_ph1)
{
    auto  f27 = stepworks::eal::curf::bind(  a_times_b_minus_c(), 10, 2, std::placeholders::_1 )(4);
    EXPECT_EQ ( f27, 16);
}


TEST (curf_test_case, curf_ph1_2)
{
    auto  f27 = stepworks::eal::curf::bind(  a_times_b_minus_c(), 10, std::placeholders::_1, 6 )(4);
    EXPECT_EQ ( f27, 34);
}

TEST (curf_test_case, curf_ph1x)
{
    auto  f27 = stepworks::eal::curf::bind(  a_times_b_minus_c(), 10, 2 );
    stepworks::ignore(f27);
}


