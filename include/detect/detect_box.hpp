//
// Created by karsten on 05.06.21.
//

#ifndef STEPWORKS_DETECT_BOX_HPP
#define STEPWORKS_DETECT_BOX_HPP


#include <type_traits>
#include <concepts>
#include <box/box.hpp>

using stepworks::bxx::box;

namespace stepworks::detect {


    template<class,
        //    template<class >class,
        //    template<typename ...> class,
                    class = void>
    struct is_box : std::false_type {
    };

    template<class Ty>
    struct is_box< Ty ,  std::void_t<
            decltype(std::declval< typename  Ty::agg_t>()),
            decltype(std::declval< typename  Ty::base_t>()),
            decltype(std::declval< typename  Ty::type>())
            > > : std::true_type  {
    };

}


#endif //STEPWORKS_DETECT_BOX_HPP
