//
// Created by kh on 15.01.21.
//

#ifndef STEPWORKS_DETECT_PUSH_BACK_HPP
#define STEPWORKS_DETECT_PUSH_BACK_HPP


#include <type_traits>

namespace stepworks::detect{



    template<typename C, typename=void>
    struct supports_push_bak : std::false_type {
    };

    template<typename C>
    struct supports_push_bak<C,
            std::void_t<
                    decltype(std::declval<C>().push_back(  std::declval<typename  C::value_type>()  ))
            > >:   std::true_type {};


}



#endif //STEPWORKS_DETECT_PUSH_BACK_HPP
