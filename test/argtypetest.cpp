#include "gtest/gtest.h"

//#include <util/argtype.hpp>
#include <util/arg_t.hpp>
#include <eal/argtuple_t.hpp>

#include <string>

int t3( std::string, int, std::string){return 1;}

TEST (argtype_test_case, t0)
{
    argtool::arg_t <1, decltype(t3) >::type  x =42;
}


TEST (argtype_test_case, argtuple_test0)
{
    stepworks::eal::argtuple_t<decltype(t3)>::args_t x("hallo",42,"world");
}

