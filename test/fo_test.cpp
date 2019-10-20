#include "gtest/gtest.h"

#include <tuple>

#include <eal/fo_t.hpp>
#include <eal/apply.hpp>
#include <eal/lazy_t.hpp>


int add2(int a, int b ) {
    return a+b;
}

using namespace stepworks::eal::fo;

TEST (fo_test_case, fo_func) {

    auto ff= ft<int,int,int> {add2};

    auto r = ff(3,7);

    EXPECT_EQ(r,10);
}

TEST (fo_test_case, fo_genfunc) {

    auto ff=  factor::gen(add2);  //ft<int,int,int>{add2};

    auto r = ff(3,7);

    EXPECT_EQ(r,10);
}

TEST (fo_test_case, fo_apply_t_genfunc) {

    auto ff=  factor::gen(add2);  //ft<int,int,int>{add2};

    auto x = ff ( decltype(ff)::arg_signature_tt( 2, 3));

    EXPECT_EQ(x,5);
}



TEST (fo_test_case, fo_lambda_functraits) {

    auto ladd = [](int a, int b) {
        return a+b;
    };
    auto ff= ft <decltype(ladd),  typename  function_traits<decltype(ladd)>::tuple_type   > { std::move(ladd)  };
    decltype( ff)::arg_signature_tt x;
    int v =  std::tuple_size< decltype(x) >::value;
    EXPECT_EQ(v,2);
}



TEST (fo_test_case, fo_has_signature) {

    auto ff=  factor::gen(add2);  //ft<int,int,int>{add2};
    auto bfnc = has_signature_t<decltype (ff)>::value;
    std::cout<<  std::boolalpha<< "\nfnc (true?) "<<bfnc;
    auto lx = [](int a) {
        return -a;
    };

    {
        auto ff=  _ft<decltype(lx) > { std::move(lx)  };
        std::cout<<  std::boolalpha<< "\nlambda (false?)"<<  "\t"<< has_signature_t<decltype(ff)>::value  ;
        EXPECT_EQ(has_signature_t<decltype(lx)>::value, false);
    }
}

TEST (fo_test_case, fo_lambda) {

    auto ladd = [](int a, int b) {
        return a+b;
    };

    auto has_signature = has_signature_t<decltype(ladd)>::value;

    EXPECT_EQ(has_signature, false);

    auto ff= ft<decltype(ladd), typename  function_traits<decltype(ladd)>::tuple_type  > { std::move(ladd)  };
    {
        auto r = ff(31,7);
        EXPECT_EQ(r,38);
    }
    {
        auto r = ff (decltype(ff)::arg_signature_tt( 2, 3));
        EXPECT_EQ(r,5);
    }

    auto  ff2 = factor::gen(ladd);
    {
        auto r = ff (decltype(ff2)::arg_signature_tt( 2, 3));
        EXPECT_EQ(r,5);
    }
}


TEST (fo_test_case, fo_lambda2) {

    auto f1 = factor::gen(    [](int a, int b) {      return a+b;    }      );
    
    auto f2 = factor::gen(    [](int a, int b) {      return a*b;    }      );
    
    auto r = f2(decltype(f2)::arg_signature_tt( 2,  f1 ( 20, 1) ) );
    
    EXPECT_EQ(r,42);
}

