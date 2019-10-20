#include "gtest/gtest.h"
#include <eal/lazy_t.hpp>


struct add2sig{
     auto operator()(int a, int b){
         std::cout<< "\n-add2sig-\n"<< a<<','<<b<<'\n';
         return a+b;
    }           
};

using stepworks::eal::lazy_t;
using stepworks::eal::_lazy_;

TEST (lazy_test_case, lazy0) {

    auto ll = _lazy_(add2sig(),1,41);
    auto r =ll();
    
    EXPECT_EQ(r,42);
}



