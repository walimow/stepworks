#include "gtest/gtest.h"
#include <step_abstract.hpp>

#include <foab.hpp>
#include <apply.hpp>
#include <util/ignore.hpp>

using stepworks::application::_;


TEST (step_test_case, impl_a0) {
    auto fplus3=[](const int& a)->int{return a+3;};
    auto app= _( fplus3);
    stepworks::ignore(app);
}

auto
     fplus3=[](const int& a)->int{return a+3;};

TEST (step_test_case, impl0) {
    
   stepworks::step<int(const int&)>::F 
//    auto
     fplus3=[](const int& a)->int{return a+3;};
    
    auto 
    s3 = stepworks::step<int(const int&)>{ _(  fplus3) };
    int r = s3(7);
    EXPECT_EQ(r,10);
    
}
