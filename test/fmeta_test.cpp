//
// Created by kh on 29.10.21.
//

#include <detect/detect_fmeta.hpp>
#include <fmeta/fnx.hpp>
#include <gtest/gtest.h>

using stepworks::fmeta::_fncx;
using stepworks::detect::no_param;

namespace {

    int fsample2(int a, int b){
        return a+b;
    }

    int fsample2minus(int a, int b){
        return a-b;
    }

    int fsample2x(int a, int b, int c){
        return (a+b)*c;
    }

    struct sfsample{;
        int operator()(int a, int b){
            return a+b;
        }
    };

}

/*
TEST (fmeta_test, detect_first){

  //  typename first_arg< decltype(fsample2) >::ret_t   x=0;
    auto t= stepworks::detect::first_arg_support<decltype(fsample2) >::value ;
    EXPECT_TRUE(t);
}

TEST (fmeta_test, detect_second){

  //  typename stepworks::detect::snd_arg< decltype(fsample2x) >::ret_t   x=0;

    auto t= stepworks::detect::second_arg_support<decltype(fsample2x) >::value ;
    EXPECT_TRUE(t);
}

TEST( fmeta_test, call2){
    auto i42= xenom::fmeta::_f_ttr(fsample2) (39,3); //xenom::fmeta::mk_f_ttr(fsample2())
    EXPECT_EQ(i42,42);
}

TEST( fmeta_test, call1x){
    auto i42= xenom::fmeta::_f_ttr(fsample2) (39)(3);
    EXPECT_EQ(i42,42);
}

TEST( fmeta_test, call1xl){
    auto i42= xenom::fmeta::_f_ttr(fsample2minus) (45)(3);
    EXPECT_EQ(i42,42);
}


TEST( fmeta_test, call1xr){
    auto i42= xenom::fmeta::_f_ttr(fsample2minus) (no_param{}, 3)(45);
    EXPECT_EQ(i42,42);
}

TEST( fmeta_test, callx){
    auto f= xenom::fmeta::_f_ttr(fsample2x) (-3);
    auto i42=f  (45,-1);
    EXPECT_EQ(i42,-42);
}

 * */

TEST( fmeta_test, fncx){
    auto fr= _fncx(fsample2x);
}

TEST( fmeta_test, fncx_1){
    //auto fr= _fncx(fsample2x);
    auto i42= _fncx(fsample2) (39,3); //xenom::fmeta::mk_f_ttr(fsample2())
    EXPECT_EQ(i42,42);
}


TEST( fmeta_test, fncx_partial){
    //auto fr= _fncx(fsample2x);
    auto fpi42= _fncx(fsample2) (39); //xenom::fmeta::mk_f_ttr(fsample2())
    auto i42 = fpi42(3);
    EXPECT_EQ(i42,42);
}