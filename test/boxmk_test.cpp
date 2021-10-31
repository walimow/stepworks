//
// Created by karsten on 25.11.20.
//
#include <gtest/gtest.h>
#include <box/def.hpp>
#include <box/box.hpp>
#include <box/util.hpp>
#include <box/mkbox.hpp>
#include <box/mkagg.hpp>
#include <vector>

#include <box/trace.hpp>

using stepworks::bxx::box;
using stepworks::bxx::box_type;
using T = int;
using BOX = box<T, std::vector>;
using BOX_T = box_type<T, std::vector>;

using stepworks::bxx::make::mk_box_v;

using stepworks::bxx::util::trace;
using stepworks::bxx::util::trace_form;


TEST (boxmake_test, test0) {

    auto r0 = mk_box_v<int, std::vector>(1);

    auto r1 = mk_box_v<int, std::vector>(41+1);

    int v =45;
    int z =v;
    EXPECT_EQ(v,z);

    auto r2 = mk_box_v<int, std::vector>( v );

     z =v;
    EXPECT_EQ(v,z);

}


//using  INL = stepworks::bxx::make::mk_aggregate;

TEST (boxmake_test, test_inl0) {
    auto v2= mk_box_v<int,std::vector>(BOX {42});
}


TEST (boxmake_test, test_inl) {

    using stepworks::bxx::make::mk_box_v;
    auto v0= mk_box_v<int,std::vector>();

    EXPECT_EQ( BOX_T ::typex(v0),1);
    EXPECT_EQ( BOX_T ::count(v0),0);

    auto v1= mk_box_v<int,std::vector>(42);

    EXPECT_EQ( BOX_T ::typex(v1),0);
    EXPECT_EQ( BOX_T ::count(v1),1);

    auto v2= mk_box_v<int,std::vector>({42});    ///will be interpreted as atom ! (?)
    EXPECT_EQ( BOX_T ::typex(v2),0);
    EXPECT_EQ( BOX_T ::count(v2),1);
    {
        auto v2= mk_box_v<int,std::vector>(BOX{42});    ///has to be explicit ...
        EXPECT_EQ( BOX_T ::typex(v2),1);
        EXPECT_EQ( BOX_T ::count(v2),1);
        trace_form<int,std::vector>( std::get< typename BOX::agg_t>(v2)," < ", " > ");
    }

    auto v3= mk_box_v<int,std::vector>({42,666});
    EXPECT_EQ( BOX_T ::typex(v3),1);
    EXPECT_EQ( BOX_T ::count(v3),2);

}


TEST (boxmake_test, test_inl2) {

    using stepworks::bxx::make::mk_box_v;
    auto v4= mk_box_v<int,std::vector>({42,1,666});

    ///BOX bb(v4);
    std::cout<< " (3?)--> " << BOX_T ::count(v4)<<"\n";
    trace<int,std::vector>( std::get< typename BOX::agg_t>(v4) );
}


/////
TEST (boxmake_test, test_inl_cmp) {

    using stepworks::bxx::make::mk_box_v;
    auto v0= mk_box_v<int,std::vector>();

    EXPECT_EQ( BOX_T ::typex(v0),1);
    EXPECT_EQ( BOX_T ::count(v0),0);

    auto v1= mk_box_v<int,std::vector>(42);

    bool b=v0<v1;

    auto bb=v0<=>v1;

    EXPECT_FALSE(b);

    EXPECT_EQ( BOX_T ::typex(v1),0);
    EXPECT_EQ( BOX_T ::count(v1),1);

    auto v2= mk_box_v<int,std::vector>({42});    ///will be interpreted as atom ! (?)
    EXPECT_EQ( BOX_T ::typex(v2),0);
    EXPECT_EQ( BOX_T ::count(v2),1);
    {
        auto v2= mk_box_v<int,std::vector>(BOX{42});    ///has to be explicit ...
        EXPECT_EQ( BOX_T ::typex(v2),1);
        EXPECT_EQ( BOX_T ::count(v2),1);
        trace_form<int,std::vector>( std::get< typename BOX::agg_t>(v2)," < ", " > ");
    }

    auto v3= mk_box_v<int,std::vector>({42,666});

    bool b2=v0<v3;
    EXPECT_TRUE(b2);

    EXPECT_EQ( BOX_T ::typex(v3),1);
    EXPECT_EQ( BOX_T ::count(v3),2);

}

