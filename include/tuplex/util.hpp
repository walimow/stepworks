//
// Created by karsten on 25.07.21.
//

#ifndef STEPWORKS_TPLUTIL_HPP
#define STEPWORKS_TPLUTIL_HPP

namespace stepworks::tuplex{

#include <tuple>

    namespace detail
    {
        template<int... Is>
        struct seq { };

        template<int N, int... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

        template<int... Is>
        struct gen_seq<0, Is...> : seq<Is...> { };

        template<typename T, typename F, int... Is>
        void for_each(T&& t, F f, seq<Is...>)
        {
            auto l = { (f(std::get<Is>(t)), 0)... };
        }
    }

    template<typename... Ts, typename F>
    void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
    {
        detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
    }


}

#endif //STEPWORKS_UTIL_HPP
