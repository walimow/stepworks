#pragma once

#include <utility>

namespace stepworks{
    
    

template < template<typename...>typename Ty, typename Head, typename ...Tail>
constexpr auto  cons_ty( Head&& h,  
                         Ty<Tail...>&&tail) -> Ty<Head,Tail...>
        {
           return Ty< Head, Tail... >   // needs appropriate constructor in type
           ( 
               std::forward<Head&&>( h), 
               std::forward<Ty<Tail...>&&>(  tail  )
           );   
               

};


};



