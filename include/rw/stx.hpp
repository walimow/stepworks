#pragma once
#include <tuple>
#include <rw/itx.hpp>

//token structure as base for reader, writer, iterable

namespace stepworks{
    
    //template <typename ...>     struct corpus;
    
    template <typename ...Types> 
    struct corpus//<Types...>
    {
        std::tuple<Types...> _data;
        std::size_t _pos=0;
        /*
        corpus(Types&&... types)  {
//            _data= std::make_tuple(types...);
//            _pos=0;
        }
        */
    };
    
    template <typename ...Types> 
    auto mk_itxcorpus(Types&&... types ){
        
        return  corpus<Types...  > { std::make_tuple ( std::move(types)...),0 }; //stepworks::itx< corpus<Types...  > { c ,0};
    }
    
/*
 * 
 *
 
  template <typename Element,typename ...Types> 
    auto mk_itxcorpus(Types&&... types ){
       return  corpus<Types...  > { std::make_tuple ( std::move(types)...),0 }; //stepworks::itx< corpus<Types...  > { c ,0};
        return  stepworks::itx< corpus<Types...  >, Element >{std::move(types)...};
    }
*/
} 

