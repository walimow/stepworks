#pragma once

#include <tuple>


namespace stepworks::tuplex{

    auto append(){ return std::make_tuple(); }  //no idea what for...
    
    template <typename Ta>
    auto append(Ta&& a){  return std::make_tuple( std::move(a)) ;}

    
    template <typename Ta, typename ...Right>
    auto append( Ta&& b,   std::tuple<Right...>&& a){         
        return std::tuple_cat(  std::make_tuple( std::move( a)),   std::move( b )    );            
    }
   
    
    
}
