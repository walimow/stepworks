//
// Created by karsten on 29.05.20.
//

#include "gtest/gtest.h"

#include <meta/base.hpp>
#include <set>
#include <iostream>

using stepworks::meta::mtyp;
using stepworks::meta::_mname;

TEST (meta_test_case, atom) {
   std::cout<< "--MI-- "<<_mname(42);    ///mtyp<42>::name();
}


TEST (meta_test_case, vect) {
    std::cout<< "--MI-- "<< _mname( std::vector<int>{1,2,99,3});    ///mtyp<42>::name();
}


TEST (meta_test_case, sett) {
    std::cout<< "--MI-- "<< _mname( std::set<int>{1,2,99,3});    ///mtyp<42>::name();
}

template <typename A, typename B, typename C>
struct abc{
    A _a; B _b; C _c;
};

template <typename A, typename B, typename C>
auto mk_abc(A a, B b, C c){
    return abc<A,B,C>{a,b,c};
}

TEST (meta_test_case, abct) {

    std::cout<< "--MI(tabc)-- "<< _mname( mk_abc(1,2,"Hallo?") );    ///mtyp<42>::name();
}

TEST (meta_test_case, tuplett) {

    std::cout<< "--MI(t)-- "<< _mname( std::make_tuple(1,"hallo",42) );    ///mtyp<42>::name();
}


TEST (meta_test_case, pairt) {

    std::cout<< "--MI(t)-- "<< _mname( std::make_pair(1,"hallo") );    ///mtyp<42>::name();
}