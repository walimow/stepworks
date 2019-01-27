
#include "gtest/gtest.h"
#include <util/matryoshka.hpp>


using stepworks::xg_struct;
using stepworks::xs_struct;
using stepworks::_getx;
//using stepworks::_refx;

template <typename...> struct mat;

template <typename H, typename ...T>
struct mat<H, T...> : mat<T...> {

    H _element;
    mat( H  a,  T ... t) :
        _element( a),
        mat<T...>( t...)
    {}

    using htype = H;
    const mat<T...>&  inner() const  {
        return (mat<T...>&) *this;
    }

    mat<T...>&  inner_ref()const  {
        return (mat<T...>&) *this;
    }
};



template <typename H>
struct mat<H> {
    H _element;
    mat(H  a) : _element(a) {
    }

};


TEST (matryoshka_test, getx)
{
    mat<int,int,int> m{ 1,2,3 };
    auto x1 = xg_struct<1, decltype(m) >::getx(m);
    EXPECT_EQ(x1,2);
}

                

TEST (matryoshka_test, _getx)
{
    mat<int,int,int> m{ 1,2,3 };
    const auto& x1 = _getx<1>(m);
    EXPECT_EQ(x1,2);
}                


TEST (matryoshka_test, setx)
{
    mat<int,int,int> m{ 1,2,3 };
    xs_struct<1, decltype(m) >::refx(m)=99;
    auto   x1 = xg_struct<1, decltype(m) >::getx(m);
    EXPECT_EQ(x1,99);
}


/*
TEST (matryoshka_test, refx)
{
    mat<int,int,int> m{ 1,2,3 };
      //xs_struct<1, decltype(m) >::refx(m)=99;
    _refx<1>( m)=99;
    auto   x1 = xg_struct<1, decltype(m) >::getx(m);
    EXPECT_EQ(x1,99);   
}*/
