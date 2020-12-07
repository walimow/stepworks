#include <gtest/gtest.h>
#include <util/singular.hpp>
#include <list>

using stepworks::singular::apply;
using stepworks::singular::mk_singular;

template< typename Ty>
int neg(Ty v){
    return  -v;
}

TEST (single_test_case, test_deconstruct_a0) {

   // auto x=  mk_singular( 42);
    auto x = apply(neg,  mk_singular( 42) );
    EXPECT_EQ(x._value,-42);
}

TEST (single_test_case, test_deconstruct_a0_b) {

   /*
    int x=42;
    apply(neg,std::move(x));
    EXPECT_EQ(x,-42);
   */
}


TEST (single_test_case, test_deconstruct_a0str) {

    //int x=42;
    
    auto s =  mk_singular<int>(42);
    auto s2 = apply(neg,std::move(s));
    EXPECT_EQ(s2._value,-42);
}