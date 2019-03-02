
#pragma once

#include <core/optional_type.hpp>

using stepworks::types::var_type;
using stepworks::types::off_type_num;

//using stepworks::types::var_t;

namespace stepworks::primary{

//simple    
    
template  <typename Ta,
    template<typename ...> typename R, 
    typename Tb, 
    template <typename ...> W >
    auto _f_ (     var_type<R<Ta>, off_type_num<Ta> > && r, Tb(*fab) (const Ta&),  W<Tb&&> w)->var_type< std::pair< var_type<R<Ta>>, W<Tb>  >{
         struct visr{
             W<Tb>&& w;
             auto operator()( const R<Ta>& r ){
                 
            } 
            
            auto operator()(const off_type_num<R<Ta>>& x){
                return 
            }
        };
        
        
        struct visa{
             
             W<Tb> && _w;
             Tb(*fab) (const Ta&);
             auto operator()(const Ta& a){
                 
         //     return     _f_( std::forward<W<Tb>&>(w) ,  a  ); 
            }
            auto operator() (const off_type_num<Ta>& a){
                
            }
             
      };  
    }
    
}
