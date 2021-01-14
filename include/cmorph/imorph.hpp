//
// Created by kh on 14.01.21.
//

#pragma once

#include <detect/detect_cmorph.hpp>

namespace  stepworks::cmorph{

    template <typename...> struct imorph;

    template <typename Ta, template<typename ...> typename Cs, typename Faa>
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            &&  stepworks::detect::supports_resize<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Ta>::value
    )
    struct imorph<Cs<Ta>, Faa >{

        auto apply( const Cs<Ta>& , Faa ){
               //auto R =
               //return Faa();
        }

    };


    template <typename Ta, template<typename ...> typename Cs, typename Tb, typename Fab>
    requires ( stepworks::detect::has_size<Cs<Ta>>::value
    &&  stepworks::detect::supports_resize<Cs<Tb>>::value
        &&  stepworks::detect::is_foab<Fab, Ta,Tb>::value
    )
    struct imorph<Cs<Ta>, Cs<Tb>,Fab>{
//        auto apply(  )
    };



    template <typename Ta, template<typename ...> typename Cs, typename Tb,
            template<typename ...> typename Cd>
            struct imorph<Cs<Ta>,Cd<Tb>>{

                    };


}