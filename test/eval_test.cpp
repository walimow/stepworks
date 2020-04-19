#include "gtest/gtest.h"
#include <eal/evaluate.hpp>
#include <eal/apply.hpp>
#include <eal/lform.hpp>

#include <tuplex/cons.hpp>
#include <tuplex/totext_t.hpp>

#include <tuplex/append.hpp>
#include <tuplex/ht.hpp>
#include <util/ignore.hpp>

using stepworks::eal::eval;
//using stepworks::les::to_text_t;

//using stepworks::les::__to_text__;

struct nine {
    int operator()()const {
        return 9;
    }
};

struct dnine {
    double operator()()const {
        return 0.9;
    }
};


struct none {
};



TEST ( evaluate_test, first )
{
    nine n9;
    //dnine d9;

    auto i1 = eval<int>::get_t((int)1.9);
    EXPECT_EQ ( i1,1 );
    EXPECT_EQ (  eval<int>::get_t(n9),9);
    EXPECT_EQ (  eval<int>::get_t(nine()),9);
}


TEST ( evaluate_test, evalauto )
{
    //nine n9;
    EXPECT_EQ ( eval_auto::get((int)1.9),1);
    EXPECT_EQ (  eval_auto::get(nine()),9);
}


int add(int first, int second) {
    return first + second;
}

template<typename T>
T add_generic(T first, T second) {
    return first + second;
}


struct  add2int {
    int operator()(const int& a, const int &b)const {
        return a+b;
    }
};

auto add_lambda = [](auto first, auto second) {
    return first + second;
};


TEST ( evaluate_test, eval_apply )
{
    nine n9;
    EXPECT_EQ ( stepworks::eal::apply(   add, std::make_pair(1, n9)), 10);
}



TEST  (evaluate_test, eval_lispObject)
{
    auto ret= stepworks::eal::ltype::make_le_t( add2int{}, 41,1 );
    auto x =ret();
    EXPECT_EQ (42, x);
}

TEST  (evaluate_test, eval_lispFunction)
{
    auto ret= stepworks::eal::ltype::make_le_t( [](int a, int b) {
        return a+b;
    }, 40,2 );
    auto x =ret();
    EXPECT_EQ (42, x);
}

using stepworks::tuplex::cons;


TEST  (evaluate_test, eval_les_cons0)
{
    auto x = cons();
    stepworks::ignore(x);
}

//#include <eval/les/totext_t.hpp>

TEST  (evaluate_test, eval_les_cons1)
{
    auto x = cons(1);
    std::cout<< x<<" (1?)\n";
    EXPECT_EQ (1,  std::tuple_size< decltype(x) >::value);
}


TEST  (evaluate_test, eval_les_cons2)
{
    auto x = cons(1,"halleluja!");
    EXPECT_EQ (2,  std::tuple_size< decltype(x) >::value);
}

TEST  (evaluate_test, eval_les_consn)
{
    auto x = cons(1, std::make_tuple( "halleluja!",876));
    EXPECT_EQ (3,  std::tuple_size< decltype(x) >::value);
}



TEST  (evaluate_test, eval_les_consnm)
{
    auto x = cons( "startswith...1",  std::make_tuple(1,2,3));
    EXPECT_EQ (4,  std::tuple_size< decltype(x) >::value);

//std::cout << x <<  "  ?\n";

}


TEST  (evaluate_test, eval_les_consnmx)
{
    auto x = cons ( std::make_tuple(1,2,3),"what?");
    std::cout << x <<  "  WHT??\n";
}

using stepworks::tuplex::ht;

TEST (evaluate_test, ht_2_test){
    auto x123 = std::make_tuple(1,2,3);
    auto xx = ht( std::move( x123) );
    std::cout << "\n1: "<< xx.first <<  "\n2: "<<xx.second;
}




