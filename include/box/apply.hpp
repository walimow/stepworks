//
// Created by karsten on 21.11.20.
//

#ifndef STEPWORKS_APPLY_HPP
#define STEPWORKS_APPLY_HPP

#include "box.hpp"
#include "wrekurs.hpp"

//using stepworks::bxx::mk_box0;



namespace stepworks::bxx{

    ///  Box->App, W&&->W


    template<typename Ty, template<typename ...> typename Aggregate, typename W>
    auto apply(  box<Ty,Aggregate> b, const W& w, typename W::value_t&& vol)->typename W::value_t{

        return  b._value.index() ?
                stepworks::iterativ_continuation( w,  std::get<typename box<Ty, Aggregate>::agg_t>(b._value), std::move(vol) )
                :
                w( std::get<typename box<Ty, Aggregate>::base_t>(b._value), std::forward< const  typename  W::value_t&& >(vol)) ;

    }

    template<typename Ty, template<typename ...> typename Aggregate, typename W>
    using appf_t =typename W::value_t(*)( const typename box<Ty,
            Aggregate>::agg_t & va,
                            const W&,
                            typename W::value_t&&,
                            void*);   /// bc rekursiv definition!


    template<typename Ty, template<typename ...> typename Aggregate, typename W>
    auto apply_f( const box<Ty,Aggregate>& b,
                  const W& w,
                  typename W::value_t&& vol
    ,
    //appf_t<Ty, Aggregate,W>    /// we prevent recursive definitions

    void*fpre
        =(void*)[](const typename box<Ty, Aggregate>::agg_t & v,const W& w, typename W::value_t&&wcx, void* pf){
        for ( const auto &e : v)
            wcx= apply_f(e, w,  std::move(wcx), (appf_t<Ty, Aggregate,W>)pf);
        return std::move(wcx);
        }
    )->typename W::value_t{
        struct vis{
            const W&   _w;
            typename W::value_t&& _vol;
            appf_t<Ty, Aggregate, W> f;

            auto operator()( const typename box<Ty, Aggregate>::base_t& v ) const {
                return    _w(v, std::move(_vol));
            }
            auto operator()( const typename box<Ty, Aggregate>::agg_t & v ) const{
                return   f(v   , _w
                      , std::move(_vol)
                      , (void*) f
                     );
            }
        };
        return  std::visit( vis{w, std::move(vol), (appf_t<Ty, Aggregate,W>)fpre}, b._value );
    }

}


#endif //STEPWORKS_APPLY_HPP
