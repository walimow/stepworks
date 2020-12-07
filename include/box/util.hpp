//
// Created by karsten on 25.11.20.
//

#ifndef BOX_UTIL_HPP
#define BOX_UTIL_HPP

#include <cstddef>
#include <box/def.hpp>

using stepworks::bxx::box;

namespace stepworks::bxx{

    ///dim0  nobox/box
    template <typename ...> struct box_dim;

    template <typename Ta> struct box_dim<Ta>{
        static const std::size_t value=0;
    };

    template<typename Ta, template<typename ...>typename Agg>
    struct box_dim< box<Ta, Agg>  >{
        static const std::size_t value=1;
    };

    template<typename Ta, template<typename ...>typename Agg>
    const std::size_t box_aggregation_size( const typename box<Ta,Agg>::agg_t& agg){
        return  agg.size();
    }

    template<typename Ta, template<typename ...>typename Agg>
    struct box_type{
        /// type (==index) 0: atom 1 ; 1:gg
        static const int typex(const typename box<Ta,Agg>::type &o){
            return o.index();
        };
        ///sym type  count : atom =-1, else agg.size  (maybe 0)

        static const int type_sz(const typename box<Ta,Agg>::type &o){
            return (o.index()) ?   box_aggregation_size<Ta,Agg>( std::get<   typename box<Ta,Agg>::agg_t >(o)) : -1;
        };
        ///real count : atom =1, else agg.size
        static const int count(const typename box<Ta,Agg>::type &o){
            return (o.index()) ? box_aggregation_size<Ta,Agg>( std::get<   typename box<Ta,Agg>::agg_t >(o)) : 1;
        };

        static const int count_total(const typename box<Ta,Agg>::type &o){
            if (!o.index())
                return 1;
            else{
                const typename box<Ta,Agg>::agg_t & a = std::get< typename box<Ta,Agg>::agg_t>(o);
                int ret=0;
                for (const auto& e: a)
                    ret+= box_type<Ta,Agg>::count_total(e);
                return ret;
            }
        };
    };

    ///universal...

    template<typename Ty>
    struct ref_wrapper{
        Ty& _ref;
        operator Ty&() {return _ref;}
    };

    template<typename Ty>
    struct cref_wrapper{
        const Ty& _cref;
        operator const Ty&() {return _cref;}
    };

}


#endif //BOX_UTIL_HPP
