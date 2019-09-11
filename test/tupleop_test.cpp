#include "gtest/gtest.h"
#include <tuple>
#include <eal/trace_t.hpp>
#include <eal/cons_t.hpp>
#include <eal/util_t.hpp>
#include <eal/partl_t.hpp>

using stepworks::eal::trace_t;

TEST(  tupleops_test, trace) {
    trace_t("hallo?");
    trace_t(std::make_tuple(1, 2, 3));
}


using stepworks::eal::cons;

TEST(  tupleops_test, cons1) {
    auto ret = cons( std::make_tuple(1,2,3), 4);
    std::cout <<"\n--1,2,3,4---\n";
    trace_t( std::move(  ret));

    const auto& cr=ret;

    std::cout <<"\n----\n";
    trace_t(  cr);
}

TEST(  tupleops_test, cons2) {
    auto ret = cons( std::make_tuple(1,2,3), 
                                      std::make_tuple(4,5,6)
                                    );
    std::cout <<"\n--1,2,3,4,5,6---\n";  
    trace_t(   ret);
}



TEST(  tupleops_test, iseq_sz) {
    auto r = stepworks::eal::sz_eq(
            std::make_tuple(1,2),
            std::make_tuple(-1,22)
        );
     EXPECT_EQ(r,true);
     
     r = stepworks::eal::sz_eq(
            std::make_tuple(1,2,0),
            std::make_tuple(-1,22)
        );
     EXPECT_EQ(r,false);
}

TEST(  tupleops_test, iseq_ls) {
    auto r = stepworks::eal::sz_ls(
            std::make_tuple(1,2),
            std::make_tuple(-1,22,4)
        );
     EXPECT_EQ(r,true);
     
     r = stepworks::eal::sz_ls(
            std::make_tuple(1,2),
            std::make_tuple(-1,22)
        );
     EXPECT_EQ(r,false);
     
     r = stepworks::eal::sz_ls(
            std::make_tuple(1,2,42),
            std::make_tuple(-1,22)
        );
     EXPECT_EQ(r,false);
}


TEST(  tupleops_test, iseq_gt) {
    auto r = stepworks::eal::sz_gt(
            std::make_tuple(1,2,7),
            std::make_tuple(22,4)
        );
     EXPECT_EQ(r,true);
     
     r = stepworks::eal::sz_gt(
            std::make_tuple(1,2),
            std::make_tuple(-1,22)
        );
     EXPECT_EQ(r,false);
     
     r = stepworks::eal::sz_gt(
            std::make_tuple(1,2),
            std::make_tuple(-1,22,42)
        );
     EXPECT_EQ(r,false);
}




using stepworks::eal::tail;
using stepworks::eal::tuple_sz;

TEST (tupleops_test, tail5){
                         
    auto t4 =  tail( std::make_tuple(1,2,3,4,5));
    trace_t(t4);
     EXPECT_EQ(4, tuple_sz(t4));
}

using stepworks::eal::part_t;

TEST (tupleops_test, partl3_5){    
    auto r = part_t<3>::left(  std::make_tuple(9,8,7,6,5)  );
    auto v24 =  std::apply( [](int a, int b, int c){return a+b+c;}, r);
    EXPECT_EQ(v24,24);      
}

/*
TEST (tupleops_test, partl3_52){    
    
    auto r = part_t<3>::left(  std::make_tuple(9,8,7,6,5)  );
    auto v24 =  std::apply( [](int a, int b, int c){return a+b+c;}, r);
    EXPECT_EQ(v24,24);      
}
*/
