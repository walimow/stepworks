//
// Created by kh on 17.01.21.
//
#pragma once
#include <box/box.hpp>
#include <optional>

using stepworks::bxx::box;

namespace  stepworks::amorph::hv {

    template<typename Ty, template<typename...> typename C>
    struct box_aggregator_position_list{
        using pos_list_t = std::vector< typename box<Ty,C>::agg_position>;
        pos_list_t _position_list;
        int    _verticality=0;
        //box_aggregator_position(const typename box<Ty,C>::agg_t & ba )
    };

    template<typename Ty, template<typename...> typename C>
    auto select_box(const box<Ty,C>& b)->std::optional<
    typename box<Ty,C>::agg_position>{
        if  (b._value.index()) {
            return
                std::optional< typename box<Ty,C>::agg_position>{ typename  box<Ty,C>::agg_position{
                    std::get<1>(b._value),
                    std::get<1>(b._value).begin() }
            };
        }
        else
            return std::optional< typename box<Ty,C>::agg_position>{};
    }

}
