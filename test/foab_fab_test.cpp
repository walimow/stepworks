#include "gtest/gtest.h"
#include <fab.hpp>
#include <foab.hpp>
#include <core/optional_type.hpp>

#include <optional>
#include <apply.hpp>
#include <util/ignore.hpp>


using  stepworks::fab;
using  stepworks::foab;
using  stepworks::make_fab;
using  stepworks::make_foab;

using stepworks::application::_;
using stepworks::application::_x;


struct xplus {
    int _k;
    using _argument_type=   int;
    using _return_type=int;
    auto operator()(const _argument_type &a)const->_return_type {
        return _f(a);
    };
    _return_type _f(_argument_type a) const {
        return a+_k;
    }
};

TEST(foab_fab_test_case,  foabfab_0) {
      
    foab<xplus> plus7{xplus{7}};
    
    auto f0 =[](){ return std::optional<int>{};};
    stepworks::ignore(f0);
    
    auto ff7= fab<foab<xplus>, stepworks::types::var_t >::make(plus7 /*, f0*/);
    stepworks::ignore(ff7);
    
}

#include <foab.first/isvalid.hpp>


TEST(foab_fab_test_case,  foabfab_1) {
      
    using stepworks::first::is_valid;
    
    
    foab<xplus> plus7{xplus{7}};
        
    auto ff7= make_fab(plus7 /*, f0*/);
    int i7=7;
    {
        auto r14=ff7.f1(7);   ///compiled casted?
        stepworks::ignore(r14);
    }
    auto r14=ff7.f1(i7);
    
    EXPECT_EQ(r14, 14);
    
    auto rfail=ff7.f0();
    
    auto b=  _x( is_valid<int>())( rfail);
    
    EXPECT_EQ( b, false );
    
}


TEST(foab_fab_test_case,  foabfab_info) {
    using stepworks::first::is_valid;
 //   using stepworks::types::apply_optional_void;
          
    foab<xplus> plus7{xplus{7}};
    
    auto finfo =[]()->stepworks::types::var_t_info<const int>{  
        return stepworks::types::off_info{};
    };
        
    auto ff7= make_fab<stepworks::types::var_t_info >(plus7 , finfo );
    auto r14=ff7.f1(7);   ///compiled casted?
    EXPECT_EQ(r14, 14);
    
}


TEST(foab_fab_test_case,  foabfab_add7) {
    
   // using stepworks::types::apply_optional_void;
      
    auto foab1 =  make_foab<const int&,int>(
        []( const  int& a)->int{ return a+7;} 
    );    
  
    auto xr14= foab1(7);
    EXPECT_EQ(xr14, 14);
    
    
    auto ff7= make_fab( //[](  
        foab1
      // make_foab<int,int>( [](const int a)->int{ return a+7;) )
     //   , [](){return 0;} 
    );

    int x=7;

      auto r14=ff7.f1(x);   ///compiled casted?


    EXPECT_EQ(r14, 14);

}

TEST(foab_fab_test_case,  foabfab_add7b) {
    
   // using stepworks::types::apply_optional_void;
    
    auto ff7= make_fab( //[](  
        make_foab<const int&,int>(
        []( const  int& a)->int{ return a+7;} 
                             )
    );

    int x=7;

      auto r14=ff7.f1(x);   ///compiled casted?

    EXPECT_EQ(r14, 14);

}
