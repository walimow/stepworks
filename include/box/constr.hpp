//
// Created by karsten on 18.11.20.
//

#ifndef STEPWORKS_CONSTR_HPP
#define STEPWORKS_CONSTR_HPP

#include <cstddef>

 #include <detect//detect_rec_writing.hpp>
//#include <detect_receptor_writer_type.hpp>

#include "def.hpp"

using stepworks::bxx::box;

namespace stepworks::bxx::gen {

    template<typename...>
    struct constr;

    template<typename Base, template<typename...> typename Aggregate>
        requires(
            stepworks::has_atref< box<Base, Aggregate>, typename box<Base, Aggregate>::agg_t, std::size_t>::value)
    struct constr<box<Base, Aggregate> > {

        static auto apply(std::size_t sz) {
            return typename box<Base, Aggregate>::agg_t{sz};
        }
        template <typename Allocator>
        static auto apply(std::size_t sz, const Allocator& alloc) {
            return typename box<Base, Aggregate>::agg_t{sz, alloc};
        }

    };



    template<typename Base, template<typename...> typename Aggregate> requires (
            stepworks::has_append<box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t >::value
            && !stepworks::has_atref< box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t, std::size_t>::value
    )
    struct constr<box<Base, Aggregate> > {
        static auto apply() {
            return typename box<Base, Aggregate>::agg_t{};
        }

        template <typename Allocator>
        static auto apply( const Allocator& alloc) {
            return typename box<Base, Aggregate>::agg_t{ alloc};
        }
    };

    template<typename Base, template<typename...> typename Aggregate> requires (
            stepworks::has_append_front< box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t >::value
            && !stepworks::has_append< box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t >::value
            && !stepworks::has_atref<box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t,  std::size_t>::value
    )
    struct constr<box<Base, Aggregate> > {

        static auto apply() {
            return typename box<Base, Aggregate>::agg_t{};
        }
        template <typename Allocator>
        static auto apply( const Allocator& alloc) {
            return typename box<Base, Aggregate>::agg_t{ alloc};
        }

    };

    template<typename Base, template<typename...> typename Aggregate> requires (
            stepworks::has_insert<box<Base, Aggregate>, typename box<Base, Aggregate>::agg_t >::value
            && !stepworks::has_append_front<box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t >::value
            && !stepworks::has_append<box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t>::value
            && !stepworks::has_atref<box<Base, Aggregate>,typename box<Base, Aggregate>::agg_t,  std::size_t>::value
    )
    struct constr<box<Base, Aggregate> > {

        static auto apply() {
            return typename box<Base, Aggregate>::agg_t{};
        }
        template <typename Allocator>
        static auto apply( const Allocator& alloc) {
            return typename box<Base, Aggregate>::agg_t{ alloc};
        }
    };


}

#endif //STEPWORKS_CONSTR_HPP
