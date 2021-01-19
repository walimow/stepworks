//
// Created by kh on 03.01.21.
//

#ifndef STEPWORKS_DETECT_TOTEXT_HPP
#define STEPWORKS_DETECT_TOTEXT_HPP

namespace stepworks::detect {

    template<typename T, typename = void>
    struct has_member_to_text
            : std::false_type {
    };

    template<typename T>
    struct has_member_to_text<T,
            std::void_t<decltype(std::declval<T>().to_text(1))>>
            : std::true_type {
    };

}

#endif //STEPWORKS_DETECT_TOTEXT_HPP
