//
// Created by kh on 16.01.21.
//

#include <gtest/gtest.h>
#include <cmorph/amorph/select.hpp>
#include <cmorph/amorph/h/process.hpp>
#include <cmorph/amorph/hv/select.hpp>
#include <box/box.hpp>
#include <vector>
#include <utility>
#include <cmorph/amorph/hv/apply.hpp>
///sel+cx

std::vector<int> vi{0,4,3,2,5,99,5,3};

struct scx_odd{
    int _pos=-1;
    auto operator()(const std::vector<int>& v, scx_odd&& here)->std::pair< std::vector<int>::const_iterator, scx_odd>{
        auto sz= (int)v.size();
        auto h = std::move(here);
        if (sz >0 && h._pos< sz){

            while ( ++h._pos < sz)
                if (v[h._pos] %2 )
                    return  std::make_pair( v.begin()+h._pos, h );
        }
        return std::make_pair(v.end(), h);
    }
};



TEST(amorph_test, selbegin){
    auto i2s= stepworks::amorph::select(  vi,scx_odd{});
   EXPECT_EQ(*(i2s.first),3);
}

using stepworks::bxx::box;

TEST(amorph_test, boxpos){
    using BOX_T =box<int, std::vector>;
    {
        BOX_T bv0(42);;
        auto s0 = stepworks::amorph::hv::select_box(bv0);
        EXPECT_FALSE(s0);
    }
    {
        BOX_T bv1({1, BOX_T({2, 3, 4}), 7});;
        auto s1 = stepworks::amorph::hv::select_box(bv1);
        EXPECT_TRUE(s1);
    }
}

#include <detect/detect_fa2box.hpp>
#include <box/mkbox.hpp>
//using stepworks::

auto fb0 = [](int a)-> box<int, std::vector>{
  return   stepworks::bxx::make::mk_box_v<int,std::vector>(  a*21);
};

TEST(amorph_test, detects1){

    auto bt = stepworks::detect::is_function_a2box<decltype(fb0),int,int, std::vector >::value;
    EXPECT_TRUE(bt);

    auto bf = stepworks::detect::is_function_a2box<decltype(fb0),int,double, std::vector >::value;
    EXPECT_FALSE(bf);
}

TEST(amorph_test, call1){
    auto bx = fb0(2);
    auto ix = bx._value.index();
    int _v=4;
    ASSERT_EQ(ix, 0);
    EXPECT_EQ( std::get<0>(bx._value),42 );
}

struct fbf0_t{
    int _v=9;
    auto operator () ( int a, fbf0_t&& o)
    -> std::pair< box<int, std::vector>, fbf0_t>{
        auto ff = std::move(o);
        return  std::make_pair( stepworks::bxx::make::mk_box_v<int, std::vector>(  a* ++ff._v    ),  ff   );
    };
};

TEST(amorph_test, call2){
    auto r = stepworks::amorph::hv::apply<int, std::vector>( fbf0_t{9} ,7);
    ASSERT_EQ(r.first.index(),0);
    EXPECT_EQ( std::get<0>(r.first),70 );
    EXPECT_EQ(r.second._v,10);
}

fbf0_t fbf0;

TEST(amorph_test, detects2){

    auto bt = stepworks::detect::is_function_aF2boxF<fbf0_t,int,int, std::vector >::value;
    EXPECT_TRUE(bt);

    auto bf = stepworks::detect::is_function_aF2boxF<fbf0_t,int,std::string, std::vector >::value;
    EXPECT_FALSE(bf);
}


auto fb2 = [](int a, int k)-> box<int, std::vector>{
    return stepworks::bxx::make::mk_box_v<int, std::vector>( k-a);
};


TEST(amorph_test, detects3){

    auto bt = stepworks::detect::is_function_aCx2box<decltype(fb2),int,int, int, std::vector >::value;
    EXPECT_TRUE(bt);

    auto bf = stepworks::detect::is_function_aCx2box<decltype(fb2),int,std::string, double, std::vector >::value;
    EXPECT_FALSE(bf);
}

TEST(amorph_test, call3){

    auto r = stepworks::amorph::hv::apply<int, std::vector,int>( fb2,7,15);
    ASSERT_EQ(r.index(),0);
    EXPECT_EQ( std::get<0>(r),8 );

}


auto fb2x = [](int a, int&& x)
        -> std::pair< box<int, std::vector> ,int>{
    return std::make_pair(stepworks::bxx::make::mk_box_v<int, std::vector>( x+a),2* std::move(x));
};

//is_function_aCx2boxCx

TEST(amorph_test, detects4){

    auto bt = stepworks::detect::is_function_aCx2boxCx<decltype(fb2x),int,int, std::vector , int>::value;
    EXPECT_TRUE(bt);

    auto bf = stepworks::detect::is_function_aCx2boxCx<decltype(fb2x),int, double, std::vector , std::string >::value;
    EXPECT_FALSE(bf);
}

TEST(amorph_test, call4){

    auto r = stepworks::amorph::hv::apply<int, std::vector,int>( fb2x,7,15);
    ASSERT_EQ(r.first.index(),0);
    EXPECT_EQ( std::get<0>(r.first),22 );
    EXPECT_EQ( r.second, 30);
}

#include <cmorph/imorph/boxtrans.hpp>
#include <box/trace.hpp>

auto fastr = [](int a)->std::string{ return "***( "+std::to_string(a)+" )***" ;};

TEST(amorph_test, boxtransfer){
    using BOX_T =box<int, std::vector>;

    BOX_T bv1({1, BOX_T({2, 3, 4}), 7});;

    //

    auto r = stepworks::imorph::box_transfer<std::string>(  bv1, fastr);    //box_support<std::string>{fastr}( bv1);
    //BOX_T
    stepworks::bxx::util::trace_form( box<std::string, std::vector>{r}, " ","\n " );

    //    auto s1 = stepworks::amorph::hv::select_box(bv1);
    //    EXPECT_TRUE(s1);

}