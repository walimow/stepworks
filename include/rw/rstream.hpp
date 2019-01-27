#pragma once


#include <foab.first/isvalid.hpp>
#include <xtypes.hpp>
#include <util/optional_type.hpp>

#include <istream>

using stepworks::types::var_t;

namespace stepworks {

template <typename Ta,
          typename Stream = std::istream,
          template <typename > typename Form = var_t>
struct rstream {
    Stream _stream;

    operator bool()const {
        return ! _stream.eof() && _stream.good();    //?
    }
};

template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form
         >
auto  _go_ ( rstream<Ta, Src, Form  >&& src)
{
    rstream<Ta, Src, Form >s =std::move(src);
    if (s)
    {
        Ta a;
        s._stream>>a;
        if (!s._stream.fail())
            return std::make_pair(Form<Ta>(a),   std::move(s));
    }
  //  else
        return  std:: make_pair( Form<Ta>(), std::move(s)) ;
}

template<typename Ta,
         typename  Stream = std:: istream,
         template <typename > typename Form = var_t>
auto make_rstream(Stream&& s ) {
    return rstream<Ta,Stream, Form  >{ std::move(s)  };
}   
    
    
    
}
