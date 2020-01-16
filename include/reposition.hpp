#pragma once

#include <type_traits>

namespace stepworks {


template <class, class=void>
struct has_reposition:  std::false_type {};

template <class R>
struct  has_reposition<R,

          std::void_t<  
          decltype( std::declval< typename R::position_t>())
           ,  decltype( get_position( std::declval<R>()  ) )      
           ,   decltype( set_position(   std::declval<R&>()  , std::declval< typename  R::position_t && >()   )    )
                         >        
        >: std::true_type {};
}
