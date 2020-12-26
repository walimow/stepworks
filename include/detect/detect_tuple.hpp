//
// Created by karsten on 21.12.20.
//

#ifndef STEPWORKS_DETECT_TUPLE_HPP
#define STEPWORKS_DETECT_TUPLE_HPP


namespace stepworks::bxx::detect {

    template<typename C, typename=void>
    struct is_tuple : std::false_type { };

    template<typename... Ts> struct is_tuple<std::tuple<Ts...>> : std::true_type {};
template<typename... Ts> struct is_tuple<const std::tuple<Ts...>> : std::true_type {};
template<typename... Ts> struct is_tuple<volatile std::tuple<Ts...>> : std::true_type {};
template<typename... Ts> struct is_tuple<const volatile std::tuple<Ts...>> : std::true_type {};

}

#endif //STEPWORKS_DETECT_TUPLE_HPP
