#include "gtest/gtest.h"
#include <foab.first/filter.hpp>
#include <util/optional.hpp>

namespace filtertest{

bool is_not_negative(const int& i){
    return i>=0;
}



}


using stepworks::first::filter;
using stepworks::types::_optional;

TEST (filter_test_case, fbase_op) {

     auto res = filter<int>{  filtertest::is_not_negative}(42);

     EXPECT_EQ( _optional(res,-1),42);
     
     res = filter<int>{  filtertest::is_not_negative}(-42);

     
    EXPECT_EQ( _optional(res,-1),-1);
     
}

//using stepworks::first::make_filter;

/*
TEST (filter_test_case, maked) {

     auto res = make_filter(  filtertest::is_not_negative)(42);

     EXPECT_EQ( _optional(res,-1),42);
     
     res = make_filter(  filtertest::is_not_negative)(-42);

     
    EXPECT_EQ( _optional(res,-1),-1);
}
*/



     
