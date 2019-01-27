#include "gtest/gtest.h"
#include <util/argtype.hpp>
#include <xtypes.hpp>
#include <foab.first/isvalid.hpp>

#include <xt.hpp>

using stepworks::first::is_valid;
//using stepworks::types::apply;
using stepworks::types::apply_optional_void;
using stepworks::types::apply_optional_type;


#include <foab.hpp>



TEST(xtypes_test,  impl_apply) {

    using stepworks::types::var_t;
    var_t<int> none;
    using Ty = decltype(none);

    auto fident_vint=stepworks::make_foab<Ty,Ty>(     stepworks::ident );
    auto echo = stepworks::types::apply<int,int>(none, fident_vint );

}



TEST(xtypes_test,  impl_apply_info) {

    using stepworks::types::var_t_info;
    var_t_info<int> none;
    using Ty = decltype(none);

    auto fident_vint=stepworks::make_foab<Ty,Ty>(     stepworks::ident );

    auto echo = stepworks::types::apply<int,int>(none, fident_vint );
}

TEST(xtypes_test,  impl_optional) {

    using stepworks::types::var_t;

    var_t<int> none;
    var_t<int> one{1};

    auto b= apply_optional_void<int,bool>( none, is_valid<int>());
    EXPECT_EQ(b,false);
    b= apply_optional_void<int,bool>( one, is_valid<int>());
    EXPECT_EQ(b, true);
}



TEST(xtypes_test,  impl_optional_info) {

    using stepworks::types::var_t_info;

    var_t_info<int > none;
    var_t_info<int> one{1};


    {
        auto b= apply_optional_void<int,bool>  (none,is_valid<int> {});
        EXPECT_EQ(b,false);
    }
    {
        auto b= apply_optional_void<int,bool>( one, is_valid<int>());
        EXPECT_EQ(b, true);
    }

}




TEST(xtypes_test,  impl_optional_type_void) {


    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;


    var_t_type<int > none;
    var_t_type<int> one{1};


    {
        auto b= apply_optional_void<int,bool>  (none,is_valid<  int > {});
        EXPECT_EQ(b,false);
    }
    {
        auto b= apply_optional_void<int,bool>( one, is_valid<int>());
        EXPECT_EQ(b, true);
    }

}



namespace test {
///extended ft0
template <typename Ta>
struct is_valid_test {

    constexpr  bool f1( const Ta&) const {
        return true;
    }
    constexpr  bool f0()const {
        return false;
    }

    template<typename Any>
    constexpr  bool ft0(const Any& )const {
        return false;
    }
};

}

TEST(xtypes_test,  impl_optional_type) {

    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;
    var_t_type<int > none;
    var_t_type<int> one{1};


    {
        auto b= apply_optional_type<int,bool>  (none, test::is_valid_test<  int > {});
        EXPECT_EQ(b,false);
    }
    {
        auto b= apply_optional_type<int,bool>( one, test::is_valid_test<int>());
        EXPECT_EQ(b, true);
    }
}

#include <foab.first/typetext.hpp>

TEST(xtypes_test,  impl_optional_to_typetext) {

    using stepworks::first::to_typetext;
    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;
    var_t_type<int > none;
    var_t_type<int> one{1};
    {
        auto s = apply_optional_type<int,std::string>  (none, to_typetext<int> {});
        std::cout <<"empty? >" << s<<"<\n";
    }
    {
        auto s = apply_optional_type<int,std::string>  (one, to_typetext<int> {});
        std::cout <<"not empty? >" << s<<"<\nb";
    }
}


TEST(xtypes_test,  impl_optional_to_typetext_1) {

    using stepworks::first::to_typetext;
    using stepworks::types::var_t_type;  //  ::types::var_t_type<int>;
    var_t_type<int > none;
    var_t_type<int> one{1};
    {
        auto s = apply_optional_type<int,std::string>  (none, to_typetext<int, 1> {});
        std::cout <<"empty? >" << s<<"<\n";
    }
    {
        auto s = apply_optional_type<int,std::string>  (one, to_typetext<int, 1> {});
        std::cout <<"not empty? >" << s<<"<\nb";
    }
}


using stepworks::types::apply_fab;


TEST(xtypes_test,  impl_wrapped_void1) {

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};

    
    //auto b= apply_optional_void<int,bool>( one, is_valid<int>());

    auto b0=  apply_fab( is_valid < int >(), one );
    EXPECT_EQ(b0,true);

    b0= apply_fab( is_valid < int >(), none );
    EXPECT_EQ(b0,false);

}

namespace test {
///extended ft0

struct is_int42_test {

    constexpr  bool f1( const int& x) const {
        return x==42;
    }
    constexpr  bool f0()const {
        return false;
    }

    template<typename Any>
    constexpr  bool ft0(const Any& )const {
        return false;
    }
};
}



TEST(xtypes_test,  impl_wrapped_void0) {

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};
    var_t_info<int> vi42{42};

    
    //auto b= apply_optional_void<int,bool>( one, is_valid<int>());

    auto b0= apply_fab( test::is_int42_test(), one );
    EXPECT_EQ(b0,false);

    b0= apply_fab( test::is_int42_test(), none );
    EXPECT_EQ(b0,false);
    
    b0= apply_fab( test::is_int42_test(), vi42 );
    EXPECT_EQ(b0,true);
}

namespace test{
    
template <typename Ta, typename Tb>    
struct conditionally_ident {
    Tb _default;
   
    constexpr  Tb f1( const Ta& x) const {
        return Tb(x);
    }
    constexpr  Tb f0()const {
        return _default;
    }

    template< typename Any>
    constexpr  Tb ft0(const Any&)const {
        return _default;
    }
};
}




TEST(xtypes_test,  impl_wrapped_void2) {

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};
    var_t_info<std::string> vs{"Halleluja!"};

    auto r = apply_fab( test::conditionally_ident<int, double>{42.42},none);
    EXPECT_EQ(r,42.42);        
}




TEST(xtypes_test,  impl_wrapped_type2) {

    using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
    var_t_info<int > none;
    var_t_info<int> one{1};
    var_t_info<std::string> vs{"Halleluja!"};

    auto r = apply_fabt( test::conditionally_ident<int, double>{42.42},none);
    EXPECT_EQ(r,42.42);    
    
}



TEST(xtypes_test,  impl_apply0) {

    using stepworks::types::var_t;  //  ::types::var_t_type<int>;
    var_t<int > none;
    var_t<int> one{1};
    auto    b0= apply_fab0( test::is_int42_test(), one );
    EXPECT_EQ(b0,false);

    b0= apply_fab0( test::is_int42_test(), none );
    EXPECT_EQ(b0,false);
}





TEST(xtypes_test,  impl_xT) {
  stepworks::xT<int>  vi;

   using stepworks::types::var_t_info;  //  ::types::var_t_type<int>;
   
  stepworks::xT<int,var_t_info>  vii;

   using stepworks::types::var_t_type;
   
   stepworks::xTt<int>  vit;

   stepworks::xTt<int,  unsigned long >  vitul;
}

/*
auto apply( const var_t_type<Ta,Tb>& a0,  const Fab& f)
-> var_t_type<Ta,Tb> {                                 
f0

*/



namespace test{
template <typename Ta, typename Tb=Ta>    
struct minus{
    Tb f1(const Ta&a)const {
        return Tb(-a);
    }
    
};

}

//TEST (foab_test_case, fapply) {
    
    
TEST(xtypes_test,  impl_apply_1) {
    stepworks::types::var_t_type<int,int> x1{1};
  
  auto res= stepworks::types::apply<int,int>(x1, test::minus<int,double>{});

}


