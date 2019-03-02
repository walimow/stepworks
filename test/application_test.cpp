#include "gtest/gtest.h"

#include <core/optional_type.hpp>

#include  <apply.hpp>

#include <iostream>
#include <set>

#include <rw/winsert.hpp>

using namespace::stepworks::application;

//using    stepworks::application::apply;
//using  stepworks::application::make;

using stepworks::types::var_t;


int f0()
{
    return -12;
};

TEST ( applcation_test_case, impl )
{
    auto two_times=[] ( const int&v ) {
        return 2*v;
    };

    auto three_times=[] ( const int&v ) {
        return 3*v;
    };

    int ( *f1 ) ( const int& ) = [] ( const int& a ) {
        return 2* a;
    };

/*
    {
        auto  r4= apply<int ( const int& ) > {two_times} ( 21 );
        EXPECT_EQ ( r4,42 );
    }*/
    {
        auto  r4=   _ ( f1 ) ( 21 );
        EXPECT_EQ ( r4,42 );
    }

    {
        var_t<int> v {};

        auto x = _ ( f1, f0 ) ( v );
        EXPECT_EQ ( x,-12 );

    }
    {
        var_t<int> v {21};
        auto x = _ ( f1, f0 ) ( v );
        EXPECT_EQ ( x,42 );
    }
}


TEST ( applcation_test_case, writer )
{
    std::set<int> w;

//    stepworks::wtype::wforward<int, std::set> wff;
    decltype(w)&& wirr= std::move(w);
    for (auto i : {
                6,3,77,1,1,-1
            }) {
       w= _( std::move(w))(i);
     
    }
    
    //std::set<int> w;
    auto sz=w.size();
  //  EXPECT_EQ(sz,5);
    std::cout<<"\t***count "<<sz<<"\n";
    for (const auto& i: w){
        std::cout<< i<<"\t*** ";
    }

}

int ffail(const stepworks::types::off_type<int>& fail_value) {
    std::cout<< "\nfailfunc called...\n";
    return fail_value._data*10;
}

TEST ( applcation_test_case, handled )
{
    int ( *f1 ) ( const int& ) = [] ( const int& a ) {
        return 2* a;
    };

    stepworks::types::var_t_type<int> x0  {  stepworks::types::off_type<int>{-42}  };

    auto r =  _(f1,ffail)(x0);
    EXPECT_EQ(r, -420);
}


