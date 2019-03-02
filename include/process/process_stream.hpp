#pragma once

#include <apply.hpp>

using stepworks::application::apply;
using stepworks::application::_;


namespace stepworks::process::stream{
    
    //ST0 >> SArg0 >> SArg1... >> ST
    
    //the stream_type: anything what _go_ handles
    
    //the stream_argument: 
    // fab, (f0,ft), Sn()
    
    template <typename...> struct _S_;
    
//a->b
    template <typename Ta, template <typename...> typename Sta,
              typename Tb, template <typename...> typename Stb
             > 
     struct _S_<Ta,Sta<Ta>, Tb, Stb<Tb>> {
         using Fab = Tb(*)(const Ta&);
         Fab _fab;
         Stb<Tb>&& _dest;
         auto operator()( Sta<Ta>&& sta ){
                        return _(_fab)(sta);
        }
         
    };     
    
}
