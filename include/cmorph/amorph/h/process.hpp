//
// Created by kh on 15.01.21.
//

#pragma once

#include <utility>
#include <detect/detect_cmorph.hpp>
#include <detect/detect_rw.hpp>
#include <detect/detect_iterable.hpp>
#include <cmorph/amorph/select.hpp>
#include "apply.hpp"


///processing const C F&& -> F   //  F&&(a)->F,b  (F is transfer with itself as context~state, Writer after it)

namespace  stepworks::amorph::h{

    //// f

    ///simple , size(d) type(no allocator!)
    template <typename Ta, typename Fab, template <typename...> typename  Cs>
    requires (
            stepworks::detect::is_forward_iterable<Cs<Ta>>::value
            &&
            stepworks::wp::is_wprocessor<Fab,Ta>::value
            &&
            stepworks::amorph::detect::context_step_support<Fab>::value
    )
    static auto process_amorphh( const Cs<Ta>& src,  Fab&& fab=Fab()){
        for (const auto & a: src)
            ///        writing                  transfer
            do {
                if (fab.step_option() != stepworks::amorph::h::skip)
                    fab = Fab::apply(std::move(fab), std::move(fab)(a));
            }while (fab.step_option()== stepworks::amorph::h::stay);
        return std::move(fab);
    }

}