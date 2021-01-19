//
// Created by kh on 14.01.21.
//

#ifndef STEPWORKS_DETECT_INDEXREF_HPP
#define STEPWORKS_DETECT_INDEXREF_HPP

#include <type_traits>

namespace stepworks::detect{


//has set[ix]
    template<typename C, typename=void>
    struct supports_set_ix_value : std::false_type {
    };

    template<typename C>
    struct supports_set_ix_value<C,
            std::void_t<
                    decltype(std::declval<C>().operator[]( std::declval<std::size_t>() ))
            > >:   // std::true_type {};   ///
            std::is_same<
                    typename C::value_type,
                    typename std::decay<
                            decltype(std::declval<C>()[std::declval<std::size_t>()])
                    >::type
            >::type
    {};




}


#endif //STEPWORKS_DETECT_INDEXREF_HPP
