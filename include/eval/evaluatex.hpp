#pragma once

#include  <type_traits>
#include  <core/optional_type.hpp>

namespace stepworks::evaluation{
    
    
template <typename Ta, template<typename...> typename Frame >
using f0_tx=    decltype(::std::declval<Frame<Ta>>() ());

    
template <typename Ta, template<typename...> typename Frame, typename Off >
using f0_t0=    decltype(::std::declval<Frame<Ta>>() ());



///Base
//template <typename R, typename Ta, 


}
