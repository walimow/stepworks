//
// Created by kh on 18.11.20.
//

#ifndef STEPWORKS_BXWRITER_HPP
#define STEPWORKS_BXWRITER_HPP

#include <detect//detect_rec_writing.hpp>
#include "def.hpp"

namespace stepworks::bxx::writer {

///context

    template<typename...>
    struct write_cx;

    template<typename Base, template<typename...> typename Aggregate> requires(
            stepworks::has_atref< box<Base, Aggregate>,typename  box<Base, Aggregate>::agg_t,  std::size_t>::value)
    struct write_cx< box<Base, Aggregate> > {

        using context_t = std::size_t;
        static auto
        apply(typename box<Base, Aggregate>::agg_t &&c_, typename box<Base, Aggregate>::type e, std::size_t sz) {
            auto c = std::move(c_);
            if (sz < c.size())
                c[sz] = std::move(e);
            return c;
        }

    };

    /*
    template<typename Base, template<typename...> typename Aggregate> requires(
            !stepworks::has_atref< box<Base, Aggregate>, typename  box<Base, Aggregate>::agg_t, std::size_t>::value)
    struct write_cx< box<Base, Aggregate> > {

        using context_t = std::size_t;
        static auto
        apply(typename box<Base, Aggregate>::agg_t &&c_, typename box<Base, Aggregate>::agg_t e, std::size_t sz) {
            auto c = std::move(c_);
            if (sz < c.size())
                c[sz] = std::move(e);
            return c;
        }

    };
*/


/// no context

    template<typename...>
    struct write;


    template<typename Base, template<typename...> typename Aggregate>
requires(         stepworks::has_append<
        typename  box<Base, Aggregate>::agg_t,box<Base, Aggregate>, std::size_t>::value
            //  && !stepworks::has_atref<   typename box< Base,Aggregate>::agg_t ,  box<Base, Aggregate>, std::size_t  >::value
)
struct write<box<Base, Aggregate> > {
static auto apply( typename box<Base, Aggregate>::agg_t && c_, typename box<Base, Aggregate>::type e) {
    auto  c = std::move(c_) ;
    c.emplace_back(e);
    return c;
}
};

template<typename Base, template<typename...> typename Aggregate>
requires(
    stepworks::has_append_front<typename box< Base,Aggregate>::agg_t,  box<Base, Aggregate>  >::value
    && !stepworks::has_append< typename box< Base,Aggregate>::agg_t,  box<Base, Aggregate> >::value
    && !stepworks::has_atref< typename box< Base,Aggregate>::agg_t,  box<Base, Aggregate> , std::size_t  >::value
)

//template<typename Base, template<typename...> typename Aggregate>
struct write<box<Base, Aggregate> > {
    static auto apply( typename box<Base, Aggregate>::agg_t && c_, typename box<Base, Aggregate>::type e) {
        auto  c = std::move(c_) ;
        c.emplace_front(e);
        return c;
    }
};

template<typename Base, template<typename...> typename Aggregate>
requires(
    stepworks::has_insert<   typename box< Base,Aggregate>::agg_t ,  box<Base, Aggregate> >::value
    && !stepworks::has_append_front<  typename box< Base,Aggregate>::agg_t ,  box<Base, Aggregate> >::value
    && !stepworks::has_append<   typename box< Base,Aggregate>::agg_t ,  box<Base, Aggregate> >::value
    && !stepworks::has_atref<   typename box< Base,Aggregate>::agg_t ,  box<Base, Aggregate>, std::size_t  >::value
)
struct write<box<Base, Aggregate> > {
static auto apply( typename box<Base, Aggregate>::agg_t && c_, typename box<Base, Aggregate>::type e) {
    auto  c = std::move(c_) ;
    c.insert(e);
    return c;
}
};


}

#endif //STEPWORKS_WRITER_HPP
