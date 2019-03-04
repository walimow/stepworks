
#pragma once 

#include <foab.first/isvalid.hpp>
//#include <xtypes.hpp>
#include <core/optional_type.hpp>
#include <algorithm>

#include <apply.hpp>

using stepworks::types::var_t;



namespace stepworks::wtype{

template <typename Ta,
          template<typename...>  typename Dest,
          template <typename > typename Form = var_t>
struct wforward {
    Dest<Ta> _stream;

    operator bool()const {
        return ! _stream.eof() && _stream.good();    //?
    }
};


    
template <typename Ta,   template<typename...>  typename Dest>
struct  insert{
  Dest<Ta>&& _dest;
    
  constexpr  Dest<Ta> f1( const Ta&a) const {  std::move( _dest).insert(a)  ;    return std::move(_dest);  }

  constexpr  bool f0()const {         return std::move(_dest);    }
  
};

  
template <typename Ta,   template<typename...>  typename Dest>
struct  push_back{
  Dest<Ta>&& _dest;
    
  constexpr  Dest<Ta> f1( const Ta&a) const {  std::move( _dest).push_back(a)  ;    return std::move(_dest);  }

  constexpr  bool f0()const {         return std::move(_dest);    }

  
};



template<typename Ta,
          template<typename...>  typename Dest,
         template <typename > typename Form
         >
auto  _go_ ( wforward<Ta, Dest, Form  >&& dest, Form<Ta>&& a_ )->wforward<Ta, Dest, Form  >{
     Form<Ta> a0 = std::move(a_);
  //   return (apply_optional_void<Ta,Dest<Ta>  >( a0, push_back<Ta, Dest>(dest) ));       
     
     return _ /*stepworks::application::apply<>*/( std::move(dest))(a0);  
     
}



template<typename Ta,
          template<typename...>  typename Dest,
         template <typename > typename Form
         >
auto  _go_ ( insert<Ta, Dest >&& dest, Form<Ta>&& a_ )->insert<Ta, Dest  >{
     Form<Ta> a0 = std::move(a_);
 //    return (apply_optional_void<Ta,Dest<Ta>  >( a0, insert<Ta, Dest>(dest) ));       

       return _ /*stepworks::application::apply<>*/( std::move(dest))(a0);  
   
    
}


template<typename Ta,
          template<typename...>  typename Dest
         >
auto  _go_ ( insert<Ta, Dest >&& dest, const Ta& a)->insert<Ta, Dest  >{
    
        dest._dest.insert(a);
       return _ /*stepworks::application::apply<>*/( std::move(dest));  
   
    
}

}
