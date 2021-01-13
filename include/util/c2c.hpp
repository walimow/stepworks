//
// Created by kh on 13.01.21.
//
pragma once

namespace stepworks::util{

    //has resize
    template<typename C, typename=void>
    struct supports_resize : std::false_type {
    };

    template<typename C>
    struct supports_resize<C,
            std::void_t<
            decltype(std::declval<C>().resize(std::size_t))
    >
    > : std::true_type {};



//has set[ix]
template<typename C, typename=void>
    struct supports_set_ix_value : std::false_type {
    };

    template<typename C>
    struct supports_set_ix_value<C,
            std::void_t<
            decltype(std::declval<C>().operator[](std::size_t))
    >
    > :// std::true_type {};   ///
     std::is_same( typename C::value_type,
                   decltype(std::decay(std::declval<C>().operator[](std::size_t)))
                   )

    //has set K (not ix)
    struct supports_kv_value : std::false_type {
    };

template<typename C>
struct supports_kv<C,
        std::void_t<
                decltype(typename C::key_type),
                decltype(std::declval<C>().operator[](C::key_type))
        >
> :// std::true_type {};   ///
        std::is_same( typename C::value_type,
decltype(std::decay(std::declval<C>().operator[]( typename C::key_type)))
)




    template <typename ...> struct c2c;


    ///set dest:
    ///sz->index
  //  template< typename Ty,  >


    ///sz->key (+key_fnc)

    ///sz->push_back

    ///fe->index (sz)

    ///fe->push_back




}
