
#pragma once

#include <set>
#include <forward_list>
#include <map>
#include <list>
#include <core/optional_type.hpp>

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
    
    template <typename Ta>
    auto _f_ (const std::list<Ta>& l){   return l.begin();}
    
    template <typename Ta>
    auto _f_ (std::list<Ta>&& l){   return l.begin();}
    
    template <typename Ta>
    auto _f_ (const std::list<Ta>& l, typename  std::list<Ta>::iterator it){ 
        return 
            it !=   l.end() ?   (var_t<Ta>) ( *it ):  var_t<Ta>{}; 
    }
    
    template <typename Ta>
    auto _f_ (std::list<Ta>&& l, typename std::list<Ta>::iterator it){
          return 
            it !=   l.end() ?   (var_t<Ta>) ( *it ):  var_t<Ta>{} ;
   }

   
    
    
    template <typename Ta, template <typename...> typename R, typename Tb=Ta, template <typename...> typename W>
    auto _f_ (const  R<Ta>& r, Tb(*fab)(const Ta&), W<Tb>&& w=W<Tb>{}){
       // fab(  )
    }
    
}
