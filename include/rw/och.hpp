
#pragma once 

#include <none.hpp>

using stepworks::_none_;

namespace stepworks{

    template <typename Ty, typename Off, typename Base = _none_>
    struct och{
        
        typedef enum{ uninit, on, off, out } Status;
        
        using element_type = Ty;
        using f_element = Status (*)( element_type, Base* );
        f_element  _f_element;

        
        using off_type = Off;
        using f_off = Status (*)( off_type,  Base* );
        f_off _f_off;
        
    };


    
}
