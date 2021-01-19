//
// Created by kh on 15.01.21.
//

#ifndef STEPWORKS_DETECT_INSERT_HPP
#define STEPWORKS_DETECT_INSERT_HPP

namespace stepworks::detect{

    template<typename C, typename=void>
    struct supports_insert : std::false_type {
    };

    template<typename C>
    struct supports_insert<C,
            std::void_t<
            decltype(std::declval<C>().insert(  std::declval<typename  C::value_type>()  ))
    > >:   std::true_type {};


}


#endif //STEPWORKS_DETECT_INSERT_HPP
