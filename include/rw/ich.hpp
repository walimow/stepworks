#pragma once
#include <none.hpp>

using stepworks::_none_;

namespace stepworks{

    template <typename Ty, typename Off, typename Base = _none_>
    struct ich{
        
        typedef enum{ uninit, on, off, out } Status;
        
        //the "main" -function
        using element_type = Ty;
        using f_element = Base (*)( element_type, Base&& );
        f_element  _f_element;
        
        //off
        using off_type = Off;
        using f_off = Base (*)( off_type,  Base&& );
        f_off _f_off;
        
       Base&& _base; 
        
       template<template <typename> typename Form>
      auto  operator()(const Form<Ty>& a){
          ///read (a)
    }
       
       ///"internal"
            ///write : Ty,base&&  ->_x(base)
    };

    /*
    ///"external" input // here writer
    
    template <typename...> struct ichw;

    
    template <typename Ty, typename Off, typename Base >
    struct ichw<Ty,Off,Base>{
        //input-channel  ("out")
        //dest-writer  ("in")
        using f_element = Base (*)( element_type, Base* );
        f_element  _f_element;
        
    }
    */
}
