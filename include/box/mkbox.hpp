//
// Created by karsten on 18.11.20.
//

#ifndef STEPWORKS_MKBOX_HPP
#define STEPWORKS_MKBOX_HPP

#include "box.hpp"


using stepworks::bxx::box;

namespace  stepworks::bxx::make{


///the variant (elementary)

///empty
    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v( )->  typename box<Ty,Aggregation>::type {
        return   typename box<Ty,Aggregation>::type (
                typename box<Ty,Aggregation>::agg_t {}
        )  ;
    }


    template <typename Ty, typename Allocation, template<typename...> typename Aggregation>
    auto mk_box_v(const Allocation& alloc )->  typename box<Ty,Aggregation>::type {
        return   typename box<Ty,Aggregation>::type (
                typename box<Ty,Aggregation>::agg_t (alloc)
        )    ;
    }

///base
/*
    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(Ty  a )->  typename box<Ty,Aggregation>::type {
        return  typename   box<Ty,Aggregation>::type ( a );
    }
*/
    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(Ty  a )->  typename box<Ty,Aggregation>::type {
        return   typename   box<Ty,Aggregation>::type ( std::forward<Ty>(a) );
    }

    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v( typename box <Ty, Aggregation>::type &&  a )->  typename box<Ty,Aggregation>::type {
        return   typename   box<Ty,Aggregation>::type ( std::forward<Ty>(a) );
    }


    ///agg
/*
    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v( typename  box<Ty,Aggregation>::agg_t&& a )->  typename box<Ty,Aggregation>::type {
        return box<Ty,Aggregation> { std::forward<Ty>(a) };
    }
*/
///copy / move
    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(   box<Ty,Aggregation>&& a )->  typename box<Ty,Aggregation>::type {
        return typename box<Ty,Aggregation>::type {
                std::forward< typename  box<Ty,Aggregation>::type>(a._value)
        };
    }

///  initializer_list -> aggregate-> box
    template <typename Base
            , template <typename...> typename Aggregation
    >
    auto mk_box_v( typename box<const Base,std::initializer_list>::agg_t&   il   )->box<Base,Aggregation>
    {
       return  box<Base,Aggregation>( il   ) ;
    }



}


#endif //STEPWORKS_MKBOX_HPP
