#include "gtest/gtest.h"
#include <util/argtype.hpp>
//#include <xtypes.hpp>
#include <foab.first/isvalid.hpp>

#include <apply.hpp>
#include <core/optional_type.hpp>
#include <util/ignore.hpp>

using stepworks::first::is_valid;
//using stepworks::types::apply;
//using stepworks::types::apply_optional_void;
//using stepworks::types::apply_optional_type;
using stepworks::application::_;
using stepworks::application::_x;


#include <foab.hpp>

using stepworks::application::_;




TEST ( xtypes_test,  impl_apply )
{

    using stepworks::types::var_t;
    var_t<int> none;
    using Ty = decltype ( none );

//    auto fident_vint=stepworks::make_foab<Ty,Ty> ( stepworks::ident );
  auto fident_vint=stepworks::make_foab0<Ty,Ty> ( stepworks::ident , -909);
    {
        auto res = stepworks::application::_ ( fident_vint ) ( int ( 42 ) );
        EXPECT_EQ ( res,42 );
    }
    bool bf0 = has_member_f0<decltype ( fident_vint ) >();
    stepworks::ignore(bf0);
    bool bb= bool ( none );
    stepworks::ignore(bb);
    {
        auto res =
                stepworks::application::_ ( fident_vint ) ( none );
        stepworks::ignore(res);
    }

}



TEST ( xtypes_test,  impl_apply_info )
{

    using stepworks::types::var_t_info;
    var_t_info<int> none;
    using Ty = decltype ( none );

    auto fident_vint=stepworks::make_foab<Ty,Ty> ( stepworks::ident );
    stepworks::ignore(fident_vint);


    //  auto echo =  stepworks::application::apply<int,int>{fident_vint}(none);
    //  auto echo = stepworks::application::_(fident_vint )(none) ;
}

TEST ( xtypes_test,  impl_optional )
{

    using stepworks::types::var_t;

    var_t<int> none;
    var_t<int> one{1};

    auto b= _x(is_valid<int>())( none );
    EXPECT_EQ ( b,false );
    b=  _x( is_valid<int>() ) ( one);
    EXPECT_EQ ( b, true );
}



TEST ( xtypes_test,  impl_optional_info )
{

    using stepworks::types::var_t_info;

    var_t_info<int > none;
    var_t_info<int> one{1};


    {
        auto b=  _x(is_valid<int> {} )( none);
        EXPECT_EQ ( b,false );
    }
    {
        auto b= _x(is_valid<int>() ) ( one);
        EXPECT_EQ ( b, true );
    }

}




TEST ( xtypes_test,  impl_optional_type_void )
{
    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;

    var_t_type<int > none;
    var_t_type<int> one{1};
    {
        auto b=   _x ( is_valid<  int > {} )(none);
        EXPECT_EQ ( b,false );
    }
    {
        auto b= _x( is_valid<int>() ) ( one);
        EXPECT_EQ ( b, true );
    }

}



namespace test
{
///extended ft0
template <typename Ta>
struct is_valid_test {

    constexpr  bool f1 ( const Ta& ) const
    {
        return true;
    }
    constexpr  bool f0() const
    {
        return false;
    }

    template<typename Any>
    constexpr  bool ft0 ( const Any& ) const
    {
        return false;
    }
};

}

TEST ( xtypes_test,  impl_optional_type )
{

    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;
    var_t_type<int > none;
    var_t_type<int> one{1};

 test::is_valid_test<  int > t0{};
    {
        auto b=   stepworks::application::apply < const decltype(t0)&> {t0}(none);
          //apply_optional_type<int,bool> ( none, test::is_valid_test<  int > {} );
        stepworks::ignore(b);
        auto b2=  _  (t0)(none);
      
        EXPECT_EQ ( b2,false );
    }
    {
        auto t0=test::is_valid_test<  int > {} ;
        auto b= _( t0)( one );
        EXPECT_EQ ( b, true );
    }
    //todo rvalue
}

#include <foab.first/typetext.hpp>

TEST ( xtypes_test,  impl_optional_to_typetext )
{

    using stepworks::first::to_typetext;
    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;
    var_t_type<int > none;
    var_t_type<int> one{1};
    {
        auto s = _ (to_typetext<int> {} ) ( none);
        std::cout <<"empty? >" << s<<"<\n";
    }
    {
        auto s = _ (to_typetext<int> {} )( one );
        std::cout <<"not empty? >" << s<<"<\nb";
    }
}


TEST ( xtypes_test,  impl_optional_to_typetext_1 )
{

    using stepworks::first::to_typetext;
    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;
    var_t_type<int > none;
    var_t_type<int> one{1};
    {
      //  auto s = apply_optional_type<int,std::string> ( none, to_typetext<int, 1> {} );
          auto s = _(to_typetext<int, 1> {} )( none);
        std::cout <<"empty? >" << s<<"<\n";
    }
    {
     //   auto s = apply_optional_type<int,std::string> ( one, to_typetext<int, 1> {} );
           auto s = _( to_typetext<int, 1> {} )( one);
        std::cout <<"not empty? >" << s<<"<\nb";
    }
}


TEST ( xtypes_test,  impl_wrapped_void1 )
{

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};


    //auto b= apply_optional_void<int,bool>( one, is_valid<int>());
    auto is_int_valid = is_valid < int >();
    //auto b0=  apply_fab ( is_valid < int >(), one );
    auto b0=  _(is_int_valid )( one );
    EXPECT_EQ ( b0,true );

    b0= _( is_int_valid )( none );
    EXPECT_EQ ( b0,false );

}

namespace test
{
///extended ft0

struct is_int42_test {

    constexpr  bool f1 ( const int& x ) const
    {
        return x==42;
    }
    constexpr  bool f0() const
    {
        return false;
    }

    template<typename Any>
    constexpr  bool ft0 ( const Any& ) const
    {
        return false;
    }
};
}



TEST ( xtypes_test,  impl_wrapped_void0 )
{

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};
    var_t_info<int> vi42{42};


    //auto b= apply_optional_void<int,bool>( one, is_valid<int>());

    auto is42=test::is_int42_test();
    
    auto b0= _(is42)( one );
    EXPECT_EQ ( b0,false );

    //b0= apply_fab ( test::is_int42_test(), none );
    
    b0= _( test::is_int42_test())( none );
    EXPECT_EQ ( b0,false );

    b0= _ ( test::is_int42_test())( vi42 );
    EXPECT_EQ ( b0,true );
}

namespace test
{

template <typename Ta, typename Tb>
struct conditionally_ident {
    Tb _default;

    constexpr  Tb f1 ( const Ta& x ) const
    {
        return Tb ( x );
    }
    constexpr  Tb f0() const
    {
        return _default;
    }

    template< typename Any>
    constexpr  Tb ft0 ( const Any& ) const
    {
        return _default;
    }
};
}


TEST ( xtypes_test,  impl_wrapped_void2 )
{
    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};
    var_t_info<std::string> vs{"Halleluja!"};

    auto r = _ ( test::conditionally_ident<int, double> {42.42})(none );
    EXPECT_EQ ( r,42.42 );
}

TEST ( xtypes_test,  impl_wrapped_type2 )
{

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none0;
    var_t_info<int> one{1};
    var_t_info<std::string> vs{"Halleluja!"};

 //   auto r = apply_fabt ( test::conditionally_ident<int, double> {42.42},none );
    
    auto r = _(test::conditionally_ident<int, double> {42.42}) (none0);
    
    EXPECT_EQ ( r,42.42 );
}

TEST ( xtypes_test,  impl_apply0 )
{
    using stepworks::types::var_t;  //  ::types::var_t_type<int>;
    var_t<int > none;
    var_t<int> one{1};
    auto b0 = _ ( test::is_int42_test() ) ( one );
    EXPECT_EQ ( b0,false );

    b0= _ ( test::is_int42_test() ) ( none );
    EXPECT_EQ ( b0,false );
}






TEST ( xtypes_test,  impl_xT )
{

    using stepworks::types::var_t;
    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    using stepworks::types::var_t_type;

    var_t_info<int> vii;

    var_t<int>  vi;

    var_t<int>  vit;

    var_t_type<int,  unsigned long >  vitul;
}


namespace test
{
template <typename Ta, typename Tb=Ta>
struct minus {
    Tb f1 ( const Ta&a ) const
    {
        return Tb ( -a );
    }
    Tb f0() const
    {
        return Tb ( 0 );
    }

};

}

TEST ( xtypes_test,  impl_apply_1 )
{
    stepworks::types::var_t_type<int> x1{1};

    test::minus<int,double> mins{};
    {
        auto res= _ ( mins ); //
        stepworks::ignore(res);
    }

    auto res= _ ( mins ) ( x1 ) ; //
    stepworks::ignore(res);

}


