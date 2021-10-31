//
// Created by kh on 06.06.21.
//

#ifndef STEPWORKS_DETECT_VARIANT_HPP
#define STEPWORKS_DETECT_VARIANT_HPP

#include <variant>
#include <type_traits>
#include <concepts>


namespace stepworks::detect {

template<typename T> struct is_variant : std::false_type {};

template<typename ...Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

template<typename T>
inline constexpr bool is_variant_v=is_variant<T>::value;

template<typename Ty>
concept Variant  = is_variant_v<Ty>;


}

#endif //STEPWORKS_DETECT_VARIANT_HPP
