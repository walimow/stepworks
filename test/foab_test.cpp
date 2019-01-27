#include "gtest/gtest.h"
#include <foab.hpp>

using stepworks::foab;

TEST (foab_test_case, fab)
{
    auto x21=foab<const int&,int>([](const int&a)->int {return a*7;})(3);
    EXPECT_EQ(x21,21);
}

struct xint {
    int _k;
    using _argument_type=   int;
    using _return_type=int;
    auto operator()(const _argument_type &a)const->_return_type {
        return _f(a);
    };
    _return_type _f(_argument_type a) const {
        return _k*a;
    }
};


TEST (foab_test_case, fbase_op) {
    auto x56= foab<xint> { xint {7} }(8);
    EXPECT_EQ(x56,56);
}

TEST (foab_test_case, fbase_opfail) {
    auto x56= foab<xint> { xint {7} }( 8.1);

    EXPECT_EQ(x56,56);    ///! conversion implicit
}

using stepworks::apply_foab;

TEST (foab_test_case, fbase_opfnc) {
    xint xii {7};
    auto x56= xii(8);  
    EXPECT_EQ(x56,56);
}


#include <cassert>

/////
    template <typename Ta, typename Tb>
    struct fab_1_0
    {
        using F = Tb(const Ta);
        const F _f;
        
        using F0 = Tb();
        const F0 _f0;
        auto f1(const  Ta& a)->Tb{
            assert(_f);
            return _f(a);
        }
        auto f0()->Tb{
            assert(_f0);
            return _f0();
        }
    };

    template <typename Foab>
    auto foab_to_fab(const Foab& foab){
        
        
    }

TEST (foab_test_case, fbase_opfail_2fab) {
    auto x56= foab<xint> { xint {7} }( 8.1);

    EXPECT_EQ(x56,56);    ///! conversion implicit
}
