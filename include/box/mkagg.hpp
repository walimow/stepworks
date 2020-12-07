//
// Created by karsten on 19.11.20.
//

#ifndef STEPWORKS_MKBOXAGG_HPP
#define STEPWORKS_MKBOXAGG_HPP

#include <initializer_list>
#include <concepts>

#include <detect/detect_rec_writing.hpp>

#include "box.hpp"
#include "constr.hpp"
#include "writer.hpp"

#include "mkbox.hpp"

#include <cassert>

using stepworks::bxx::gen::constr;

using stepworks::bxx::make::mk_box_v;

namespace  stepworks::bxx::make{

    ///make aggregate types

    template <typename ...> struct mk_aggregate;
///vectorlike, array etc: access on  [cx]
    template <typename Base, template <typename...> typename Aggregate>
        requires(   stepworks::has_atref<  box<Base, Aggregate>, typename box<Base, Aggregate>::agg_t,  std::size_t>::value)
    struct mk_aggregate<  box<Base,Aggregate > > {

        ///index, size ~vector
        template<template<typename...> typename Input>
        ///=std::initialzer_list

        static auto apply( const typename box<Base, Input>::agg_t &inlst) {
            auto sz = inlst.size();
            auto &&bo = constr<box<Base, Aggregate>>::apply(sz);
            std::size_t k = 0;
            for (const auto e: inlst) {
                bo = stepworks::bxx::writer::write_cx<box<Base, Aggregate> >::apply(std::move(bo), mk_box_v(e), k++);
            }
            return std::move(bo);
        }


        static auto apply_inl(
                             std::initializer_list<std::variant<Base,
         typename box<Base, Aggregate>::agg_t > > inlst) {

            auto sz = inlst.size();
            auto &&bo = constr<box<Base, Aggregate>>::apply(sz);
            std::size_t k = 0;

            struct {

                auto operator()(Base b) const ->typename box<Base, Aggregate>::type{
                    return typename box<Base, Aggregate>::type{std::move(b)};
                }

                auto operator()( typename box<Base, Aggregate>::agg_t b) const {
                    return typename box<Base, Aggregate>::type(std::move(b));
                }

            }vis;

            for ( auto&& e: inlst) {

              typename box<Base, Aggregate>::type&& ee =           std::visit(vis,
                                       std::move(e)
                                      );
              bo =  stepworks::bxx::writer::write_cx<
                      box<Base, Aggregate>
                              >::apply (  std::move(bo),
                                    ee

                                      , k++);
            }
            return std::move(bo);
        }



        static auto apply(
         //       typename box<Base, std::initializer_list std::initializer_list>::agg_t
                std::initializer_list<  box<Base, Aggregate>                 >
                inlst) {
            auto sz = inlst.size();
            auto &&bo = constr<box<Base, Aggregate>>::apply(sz);
            std::size_t k = 0;
            for (const auto e: inlst) {
                bo = stepworks::bxx::writer::write_cx<box<Base, Aggregate> >::apply(std::move(bo), mk_box_v(e), k++);
            }
            return std::move(bo);
        }


        template<typename Allocator, template<typename...> typename Input>
        ///=std::initialzer_list
        static auto apply(typename box<Base, Input>::agg_t &&inlst, const Allocator& alloc) {
            auto sz = inlst.size();
            auto &&bo = constr<box<Base, Aggregate>>::apply(sz, alloc);
            std::size_t k = 0;
            for (const auto e: inlst) {
                bo = stepworks::bxx::writer::write_cx<box<Base, Aggregate> >::apply(std::move(bo), mk_box_v(e), k++);
            }
            return std::move(bo);
        }

        };




    template <typename Base, template <typename...> typename Aggregate>
    requires(   stepworks::has_append< typename box<Base, Aggregate>::agg_t, box<Base, Aggregate>, std::size_t>::value
        || stepworks::has_append_front< typename box<Base, Aggregate>::agg_t, box<Base, Aggregate>, std::size_t>::value
        || stepworks::has_insert< typename box<Base, Aggregate>::agg_t, box<Base, Aggregate>, std::size_t>::value
    )
    struct mk_aggregate<  box<Base,Aggregate > >{
        template< template <typename...> typename Input>  ///=std::initialzer_list
        static auto apply( const typename box<Base, Input>::agg_t& inlst){
            auto&&  bo = constr< box<Base,Aggregate>>::apply();
            for (const auto e: inlst){
                bo =   stepworks::bxx::writer::write_cx< box< Base,Aggregate> >::apply( std::move(bo), mk_box_v(e) );
            }
            return std::move(bo);
        }

    };

    template <typename Base, template <typename...> typename Aggregate>
    requires(
             std::is_same<
            typename  box<Base, Aggregate>::agg_t,
            typename  box<Base, std::initializer_list>::agg_t
            >::value
    )
    struct mk_aggregate<  box<Base,Aggregate > >{
        template< template <typename...> typename Input>  ///=std::initialzer_list
        static auto apply(


                const typename box<Base, Input>::agg_t& inlst){
            auto&&  bo = constr< box<Base,Aggregate>>::apply();
            for (const auto e: inlst){
                bo =   stepworks::bxx::writer::write_cx< box< Base,Aggregate> >::apply( std::move(bo), mk_box_v(e) );
            }
            return std::move(bo);
        }

            static auto apply_inl(
                std::initializer_list<std::variant<Base,
                        typename box<Base, Aggregate>::agg_t > > inlst){

       //     auto r = std::get<>inlst;

/*
            switch (inlst.index()) {
                case 0:
                    ;
                case 1:
                    std::get< >

            }
  */
assert(false); ///std::initializer ("in itself") dont work ..... (yet?)
            return std::initializer_list< box<Base, Aggregate> >{};
        }

    };




}

namespace  stepworks::bx{

/*
    template <typename Ty , template <typename...> typename Aggregation>
    box<Ty, Aggregation>::box( std::initializer_list<  std::variant < Ty,             box<Ty,Aggregation>  >> il){

      //    _value = stepworks::bx::make::mk_aggregate< box<Ty, Aggregation> >::apply(std::move(il));   // mk_box_value<Ty, Aggregation>(std::move(il));
    }
*/

}

#endif //STEPWORKS_MKBOXAGG_HPP
