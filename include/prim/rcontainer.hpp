
#pragma once

#include <set>
#include <forward_list>
#include <map>
#include <util/optional_type.hpp>

using stepworks::types::var_t;

/// the 'primary' operation

namespace stepworks::primary{

    template<typename Ta>
    auto _f_(  std::pair<  std::set<Ta> ,typename std::set<Ta>::iterator  > && s)
    ->std::pair<
             std::pair<  std::set<Ta> ,typename std::set<Ta>::iterator  > 
             ,
             var_t<Ta>
             >
        {
       var_t<Ta> r;
       if (s.first.end() != s.second ){
           r=*s.second ++;
       }
       return make_pair(std::move(s), std::move(r));
    }
    
    
    template<typename Ta>
    auto _f_(  std::pair<  std::forward_list<Ta> ,typename std::forward_list<Ta>::iterator  > && s)
    ->std::pair<
             std::pair<  std::forward_list<Ta> ,typename std::forward_list<Ta>::iterator  > 
             ,
             var_t<Ta>
             >
        {
       var_t<Ta> r;
       if (s.first.end() != s.second ){
           r=*s.second ++;
       }
       return make_pair(std::move(s), std::move(r));
    }
    
    
}
