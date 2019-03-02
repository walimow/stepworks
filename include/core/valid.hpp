#pragma once

#include <core/optional_type.hpp>

#include <apply.hpp>
#include <none.hpp>
#include <foab.first/isvalid.hpp>

namespace stepworks::types{
    
    template <typename Ta>
    bool _valid_(const Ta&)  {return true;}
    
    
    bool _valid_ (const stepworks::_none_&){ return false;}
 
   template <typename Ta, template <typename > typename Form>
    bool _valid_(const Form <Ta>&a)  {
        return   stepworks::application::apply{is_valid<Ta>()}( a );
        // return ( apply_optional_void<int,bool>( va, is_valid<Ta>() )) ? *va : _default;
    }
    
    
    
}
