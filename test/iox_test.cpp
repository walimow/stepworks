#include "gtest/gtest.h"
#include <util/iox.hpp>
/*
#include <iostream>
#include <vector>
#include <forward_list>
#include <deque>
#include <rw/wforward.hpp>
#include <core/optional.hpp>
*/

using stepworks::iox::ost_t;

TEST (iox_test, write_0) {
    ost_t<std::ostream,std::string> outp{std::cout, "-->", "<--" };
    outp.out(42);
    outp.out("Hallo?....\n");
}

