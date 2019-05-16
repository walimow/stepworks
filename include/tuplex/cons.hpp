#pragma once

#include <tuple>
#include <util/cons.hpp>

namespace stepworks::tuplex{
    
       
    auto cons(){ return std::make_tuple(); }  //no idea what for...
    
    template <typename Ta>
    auto cons(Ta&& a){  return std::make_tuple( std::move(a)) ;}

    
    template <typename Ta, typename ...Right>
    auto cons( Ta&& a,   std::tuple<Right...>&& b){         
        return std::tuple_cat(  std::make_tuple( std::move( a)),   std::move( b )    );            
    }
    
    
    template <typename Ta, typename Tb>
    auto cons(Ta&& a, Tb&& b){
        
        return std::make_tuple(std::move(a), std::move(b));
    }
    
    
    template <typename Ta, typename Tb>
    auto cons(const Ta& a, const Tb& b){
        
        return std::tuple_cat(a,b);
    }
        
      //  return     std::make_tuple( std::move(a), std::move(b) ) ;}
      
      // std::tuple_cat( std::move(a),    std::move(b) );
       // stepworks::cons_ty(std::move(a), std::make_tuple( std::move(b)));
       
       
/*
    template <typename Ta, typename ...Right>
    auto cons(Ta&& a,  std::tuple<Right...>&& b){  
       
        return std::tuple_cat( std::move( a),  std::move( b)     );
    
        
    }*/
    
    
    template <typename Ta, typename ...Right>
    auto cons(const Ta& a,  const std::tuple<Right...>& b){         
        return std::tuple_cat(  a,  b     );            
    }
    
    
    
    
    
}
