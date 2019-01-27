#pragma once

#include <foab.hpp>

#include <foab/reader.hpp>
#include <foab/reader0.hpp>

#include <foab/writer.hpp>
#include <foab/warg.hpp>

using stepworks::process::writer::warg_s;

namespace stepworks::process::processing{
    /*
    template <typename R, typename Ta>
    using Reader_Foab= stepworks::foab<R, std::pair<R, Ta>>;
    
    template <typename R, typename Ta, template <typename> typename FormA >
    using Reader0_Foab = stepworks::foab<R, std::pair<R, FormA<Ta>>>;
    
    template <typename R, typename Ta, template <typename> typename FormR , template <typename> typename FormA>
    using Reader00_Foab = stepworks::foab<R, std::pair< FormR<R>, FormA<Ta>>>;
    
    template<typename W, typename Ta>
    using Writer_Foab = stepworks::foab< warg_s<W,Ta> >;
    
    */
    
    template<template <typename> typename R, template <typename > typename W,typename Ta //, template <typename> FormA
    >
    struct processing{
       _Reader0<R,Ta> _reader;
       _Writer< W<Ta>, Ta > _writer;
      processing(_Reader0<R,Ta> r,  _Writer< W<Ta>, Ta > w)
      :_reader(r), _writer(w)
      { }
       /// no break!, single step
       auto operator()( R<Ta>&& r, W<Ta>&&w)->std::pair< R<Ta>,W<Ta>>{
           bool valid = (r);
           auto ra= _reader(r);
           return std::make_pair(ra.first, _writer(  warg_s<W<Ta>,Ta>{ std::move(w), std::move(ra.second) }  ));
       }
       
       ///endless..., just a test  (iterative.)
       auto run(R<Ta>&& r_, W<Ta>&&w)->std::pair< R<Ta>,W<Ta>>{
           R<Ta> r = std::move(r);
           while (r){       ///R()->bool 'is_valid_reader'~ !eof
               auto ra=(*this)(std::move(r), std::move(w) );
                r = std::move(r);
           }
           return std::make_pair( r, std::move(w) );
        }
                
    
       /*
       auto operator()( R>&& r, W&&w)->std::pair< R,W>{
           auto ra= _reader(r);
           return std::make_pair(ra.first, _writer(  warg_s<W,Ta>{ std::move(w), std::move(ra.second) }  ));
       }
      */
       
        /*
        template < typename W>
        auto operator()( Reader<R,Ta>&& r, _Writer< W, Ta >&&w)->std::pair< Reader<R,Ta>, Writer<W, Ta>>{
                  //   std::move(r)
        }
        
        
        
        template <template<typename> typename Writer, template <typename> typename FormR >
        auto operator()(Reader<Ta>&& r, Writer<Ta>&&w)->std::pair< FormR<Reader<Ta>>, Writer<Ta>>{
            
        }
        
        template <template<typename> typename Writer, template <typename>  typename FormR >
        auto operator()(FormR<Reader<Ta>>&& r, Writer<Ta>&&w)->std::pair< FormR<Reader<Ta>>, Writer<Ta>>{
            
        }
        
        template <template<typename> typename Writer, template <typename>  typename FormW >
        auto operator()(Reader<Ta>&& r, Writer<Ta>&&w)->std::pair< Reader<Ta>, FormW<Writer<Ta>>>{
            
        }
        
        template <template<typename> typename Writer, template <typename>  typename FormW >
        auto operator()(Reader<Ta>&& r, FormW< Writer<Ta>>&&w)->std::pair< Reader<Ta>, FormW<Writer<Ta>>>{
            
        }
        
        template <template<typename> typename Writer, template <typename>  typename FormR, template <typename>  typename FormW >
        auto operator()(Reader<Ta>&& r, Writer<Ta>&&w)->std::pair< FormR< Reader<Ta>>, FormW<Writer<Ta>>>{
            
        }
        
        template <template<typename> typename Writer, template <typename>  typename FormR, template <typename>  typename FormW >
        auto operator()(FormR<Reader<Ta>>&& r, FormW<Writer<Ta>>&&w)->std::pair< FormR< Reader<Ta>>, FormW<Writer<Ta>>>{
            
        }
///////
        template <template <typename , typename>  typename Transform, template<typename> typename Writer, typename Tb=Ta>
        auto operator()(Reader<Ta>&& r, Transform<Ta,Tb>,  Writer <Tb>&&w)->std::pair< Reader<Ta>, Writer<Tb>>{
            
        }
        
        template <template <typename , typename>  typename Transform, template<typename> typename Writer, template <typename> typename FormR , typename Tb=Ta>
        auto operator()(Reader<Ta>&& r, Transform<Ta,Tb>,  Writer<Tb>&&w)->std::pair< FormR<Reader<Tb>>, Writer<Ta>>{
            
        }
        
        template <template <typename , typename>  typename Transform,template<typename> typename Writer, template <typename>  typename FormR , typename Tb=Ta>
        auto operator()(FormR<Reader<Ta>>&& r, Transform<Ta,Tb>, Writer<Tb>&&w)->std::pair< FormR<Reader<Tb>>, Writer<Ta>>{
            
        }
        
        template <template <typename , typename>  typename Transform,template<typename> typename Writer, template <typename>  typename FormW , typename Tb=Ta>
        auto operator()(Reader<Ta>&& r, Transform<Ta,Tb>, Writer<Tb>&&w)->std::pair< Reader<Ta>, FormW<Writer<Tb>>>{
            
        }
        
        template <template <typename , typename>  typename Transform,template<typename> typename Writer, template <typename>  typename FormW , typename Tb=Ta>
        auto operator()(Reader<Ta>&& r, Transform<Ta,Tb>, FormW< Writer<Tb>>&&w)->std::pair< Reader<Ta>, FormW<Writer<Tb>>>{
            
        }
        
        template <template <typename , typename> typename Transform,template<typename> typename Writer, template <typename>  typename FormR, template <typename>  typename FormW , typename Tb=Ta>
        auto operator()(Reader<Ta>&& r, Transform<Ta,Tb>, Writer<Tb>&&w)->std::pair< FormR< Reader<Ta>>, FormW<Writer<Tb>>>{
            
        }
        
        template <template <typename , typename> typename Transform,template<typename> typename Writer, template <typename>  typename FormR, template <typename>  typename FormW , typename Tb=Ta>
        auto operator()(FormR<Reader<Ta>>&& r, Transform<Ta,Tb>, FormW<Writer<Tb>>&&w)->std::pair< FormR< Reader<Ta>>, FormW<Writer<Tb>>>{
            
        }
*/        
        
    };
    
    
}
