//
// Created by kh on 15.01.21.
//

#pragma once

#include <utility>
#include <detect/detect_cmorph.hpp>
#include <detect/detect_rw.hpp>
#include <detect/detect_iterable.hpp>


///processing const C F&& -> F   //  F&&(a)->F,b  (F is transfer with itself as context~state, Writer after it)

namespace  stepworks::imorph{

    //// f

    ///simple , size(d) type(no allocator!)
    template <typename Ta, typename Fab, template <typename...> typename  Cs>
    requires (
            stepworks::detect::is_forward_iterable<Cs<Ta>>::value
            &&
            stepworks::wp::is_wprocessor<Fab,Ta>::value
    )
    static auto process_imorph( const Cs<Ta>& src,  Fab&& fab=Fab()){
        for (const auto & a: src)
            ///        writing                  transfer
           fab = Fab::apply(  std::move(fab), std::move(fab) (a)) ;
        return std::move(fab);
    }

}