#pragma once

#include <core/optional.hpp>

using stepworks::types::_asserted;

namespace  stepworks::application {

template <typename Ta,   template <typename> typename Reader,    typename  Dest>
struct apply< Reader<Ta>, Dest >
{
    Dest&& _dest;
    Reader<Ta>&& r;

    auto operator () (   ) ->  Dest
    {
        auto ra=   _go_(r);
        return ra.first() ?
               apply{  std::move(_dest)(  _asserted<Ta>(ra.first)), std::move(ra.second)  }()   //build apply' with written dest and reader'
                       :
                       std::move(_dest);
    };
};

template <typename Ta,template <typename...> typename Reader, typename Dest>
auto _(Dest&& dest, Reader<Ta>&& r){
    return apply< Reader<Ta>, Dest >{ std::move(dest),r  };
}



    
}
