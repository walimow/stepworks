#include "gtest/gtest.h"
#include <rw/wstream.hpp>
#include <rw/wforward.hpp>

#include <util/optional_type.hpp>

#include <iostream>
#include <list>


TEST(wtype_test,  wstream_cout) {
    
    stepworks::wstream<int>  ws{ std::move(  std::cout) };
    stepworks::_go_(std::move(ws),42);    
}


using stepworks::types::var_t;
using stepworks::types::var_t_info;

/////apply


using stepworks::wstream;


TEST(wtype_test,  wstream_cout_opt) {
    
        wstream<int>  ws{ std::move(  std::cout) };
       
        auto try_to_implement_wfoab=  decltype(ws)::wfoab{ };
        

        var_t<int>  v42( 4002);
        
        stepworks::fwrite_ab<int, wstream<int>::wfoab&& >  fiout;
            
        std::cout<<"\n";
 
        auto&& r=  ws.write()( 1312, wstream<int>{  std::move(std::cout) } ) ;
            //return  wstream<int>{r};
     std::cout<<"\n";
 
        stepworks::apply_optional<int,  wstream<int> >( v42 , 
                                                        wstream<int>{  std::move(std::cout)} , 
                                                        ws.write()
                                                      ); 
};
        

TEST(wtype_test,  wstream_cout_opt2) {
   /* 
      stepworks::wtype::wstream<int>  ws{ std::move(  std::cout) };

     stepworks::wtype::_go_
     <int, std::ostream , var_t > 
     (std::move(ws), var_t<int>( 42) );    
  */

        wstream<int>  ws{ std::move(  std::cout) };
       
        auto try_to_implement_wfoab=  decltype(ws)::wfoab{ };
        

    //    var_t<int>  v42( 4002);
        
        stepworks::fwrite_ab<int, wstream<int>::wfoab&& >  fiout;
            
        std::cout<<"\n";
 
        auto&& r=  ws.write()( 1312, wstream<int>{  std::move(std::cout) } ) ;
            //return  wstream<int>{r};
     std::cout<<"\n";
 
        stepworks::apply_optional<int,  wstream<int> >( 4112 , 
                                                        wstream<int>{  std::move(std::cout)} , 
                                                        ws.write()
                                                      ); 
   
}


TEST(wtype_test,  wforward) {
    
      stepworks::wforward<int, std::list>  ws{ std::list<int>()  };

     auto r =  stepworks::_go_      (std::move(ws),  42 );    
      EXPECT_EQ(r._dest.size(),1);
      EXPECT_EQ(*r._dest.begin(), 42);
}


TEST(wtype_test,  wforward0) {
    
      stepworks::wforward<int, std::list>  ws{ std::list<int>()  };
      
      
      auto r=stepworks::_go_ (std::move(ws),         var_t<int>( 42) );    
      EXPECT_EQ(r._dest.size(),1);
      EXPECT_EQ(*r._dest.begin(), 42);
 
}


// using F =  var_t_info;


TEST (wtype_test,  w_vartx){
    using Ta=int;
    using Tb =int;
   
//    template <typename T>
   
    //using Src = std::list;
    using W =   stepworks::wforward<Ta, std::list, var_t>::wfoab;      
    
    auto f =   []( const Ta& a,W&& w_)->W{ auto w=std::move(w_); w._dest.push_back(a); return std::move(w);} ;
    
    //std::list<int> inout;
    
//    stepworks::foab_rrb<  var_t<Ta> , std::list<  int > > fnco{   std::move(std::list<int>()) , f  };
      
}


TEST(wtype_test,  wforward0x) {

    using stepworks::types::var_t_info;
    
      stepworks::wforward<int, std::list,var_t_info>  ws{ std::list<int>()  };
      
      auto r=stepworks::_go_
      <int, std::list, var_t_info>
      (std::move(ws),         var_t_info<int>( 42) );    
      EXPECT_EQ(r._dest.size(),1);
      EXPECT_EQ(*r._dest.begin(), 42);

}
