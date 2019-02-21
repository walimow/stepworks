#pragma once


#include <foab.first/isvalid.hpp>
#include <xtypes.hpp>
#include <util/optional_type.hpp>

///@todo....

namespace stepworks{
    
    using stepworks::types::var_t;
    
    //the common Readeable Type
    
    
    template < typename... >struct sel;
    
    //
    template <typename Ta, template <typename... >  typename Src, typename Key, typename ...Context>
    struct sel<Ta, Src<Ta>,Key, Context... >:  sel<Ta, Src<Ta>, Context...>{
        
        const   sel<Ta, Src<Ta>, Context...>& next()const{
            return (const sel<Ta, Src<Ta>, Context...>&) *this;
        }
    };
    
    
    
    
    ///~maplike functions
    template <typename Ta, template <typename... > typename Src, typename Key>
    struct sel<Ta, Src<Ta>, Key  > {
         const Src<Key, Ta>& _src;           
        
         template< template <typename > typename Form =  var_t >
         auto operator [](const Key& k)->Form<Ta>{ 
            auto it = _src.find(k);
            return it == _src.end() ? *it : Form<Ta>();
        }
    };
    
    
    
    
    
}
