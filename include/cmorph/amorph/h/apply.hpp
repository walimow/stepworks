//
// Created by kh on 15.01.21.
//

#pragma once

#include <cmorph/amorph/select.hpp>
#include <cmorph/imorph/apply.hpp>
#include <box/box.hpp>
#include <box/boxm.hpp>



namespace  stepworks::amorph::h {

    using stepworks::bxx::box;

    using eSel = enum {
        eDefault=0, next, skip, stay
    };

    template <typename Ta, template<typename ...> typename Cs, typename Context,
        template<typename ...> typename Cd=Cs, typename Tb=Ta >
    auto mk_box(  Cs<Ta>& src, box<Tb,  Cs>&& dest_=box<Tb, Cs>{}){
        auto dest = std::move(dest_);
        /// ?
        return dest;
    }



}

