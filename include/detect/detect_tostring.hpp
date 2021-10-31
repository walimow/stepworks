//
// Created by kh on 07.12.20.
//

#ifndef STEPWORKS_DETECT_TOSTRING_TEST_HPP
#define STEPWORKS_DETECT_TOSTRING_TEST_HPP

namespace stepworks::detect {

    template<typename C, typename=void>
    struct supports_tostring : std::false_type {
    };

    template<typename C>
    struct supports_tostring<C,
            std::void_t<
            decltype(std::to_string( std::declval<C>()))
        >
    > : std::true_type {};

}

#endif //STEPWORKS_DETECT_TOSTRING_TEST_HPP
