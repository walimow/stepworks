#pragma once


#include <foab.first/isvalid.hpp>
//#include <xtypes.hpp>
#include <core/optional_type.hpp>

#include <istream>
#include <fstream>

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

template< typename  Stream = std:: istream
         >
auto make_rstream0( const std::string& path )->stepworks::types::var_t_type<std::ifstream> {
     auto&& ifs=std::ifstream (path , std::ifstream::in);
    
    if (ifs.fail())
        return stepworks::types::off_type<std::ifstream>{ std::move(ifs)}; 
    else
        return   std::move(ifs);
    };    
}
/*
template<typename Ta,
         typename  Stream = std:: istream,
         template <typename ...>typename  Dest,
         template <typename > typename Form = var_t>
struct apply <Ta, Stream, Dest<Ta>> {
    Stream &&  _ist;
    //Dest<Ta>&&  _dest;
    auto operator()(Dest<Ta> &&  d)  ->Dest<Ta>{
        if (_ist.bad())
            return std::move(d);
        Ta a;
        _ist>> a;
        if (_ist.fail())
            return std::move(d);
        else
            return apply{ std::move(_ist) }(std::move(dest.f1(a)) ) ;   
    }
};
*/
