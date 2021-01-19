//
// Created by karsten on 19.01.21.
//

#ifndef STEPWORKS_BOXTRANS_HPP
#define STEPWORKS_BOXTRANS_HPP

#include <box/box.hpp>
#include <cmorph/imorph/apply.hpp>
#include <detect/detect_foab.hpp>

using stepworks::bxx::box;

namespace  stepworks::imorph {


    template< typename Tb,typename Ta, template <typename ...> typename Cs,
            typename Fab,
            template<typename ...> typename Cd=Cs>
    requires ( stepworks::detect::is_foab<Fab,Ta,Tb>::value)
    struct box_support{
        Fab _fab;
        inline auto  apply_ab( const Ta& a ){
            return  _fab(a);
        }

        inline auto apply_box_t_ab(const typename box<Ta, Cs>::type & src)const ->typename box<Tb,Cd>::type {

             auto x = src.index();
        if (!x)
            return  _fab( std::get<0>(src));
        else {

            return apply_box_agg_ab(std::get<1>(src), typename box<Tb, Cd>::agg_t{});
        }

        }

        auto   operator () (const  box<Ta, Cs>& src) const ->box<Tb,Cd> {
            return  apply_box_t_ab(src);
        }

        inline typename  box<Tb,Cd>::agg_t apply_box_agg_ab( const typename box<Ta,Cs>::agg_t& src , typename  box<Tb,Cd>::agg_t&& dest
        ) const
        {
            return    stepworks::imorph::apply<
                     box<Ta, Cs>,  //"Ta"
                     box_support<Tb,Ta,Cs,Fab,Cd>  //"Faa"
            //,  Cs
            >(  src, std::move(dest), *this) ;
        }

        auto   operator () (const typename box<Ta, Cs>::agg_t & src) const {
            return  this->apply_box_agg_ab( src);
        }

    };

    template< typename Tb,typename Ta, template <typename ...> typename Cs,
            typename Fab,
            template<typename ...> typename Cd=Cs>
    requires ( stepworks::detect::is_foab<Fab,Ta,Tb>::value)
    auto  box_transfer(const box<Ta, Cs>& src, const Fab& fab){
        return   stepworks::imorph::box_support<Tb,Ta, Cs, Fab, Cd>{fab}( src);

    }


}

#endif //STEPWORKS_BOXTRANS_HPP
