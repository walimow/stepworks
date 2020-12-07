
#ifndef BOX_IMPL_HPP
#define BOX_IMPL_HPP

//#include <detect/>
#include <sstream>

#include "def.hpp"
#include "mkagg.hpp"


using  stepworks::bxx::make::mk_aggregate;

namespace stepworks::bxx{





    template <typename Ty , template <typename...> typename Aggregation>
    box<Ty, Aggregation>::box( std::initializer_list<
               // std::variant < Ty,
              typename  box<Ty,Aggregation>::type
                > il
    ){
     ///TODO Modules   _value =   stepworks::bx::make::mk_aggregate<box< Ty,Aggregation  >>apply<>

        _value = mk_aggregate<  box<   Ty, Aggregation>>::apply_inl
              // <std::initializer_list <  typename           box<Ty,Aggregation  >::agg_t  >
                        (il );

    }




template<typename Ty,template <typename...>  typename Aggregation>
template<typename I, typename>
box<Ty, Aggregation>::box(std::initializer_list<box<Ty, Aggregation>::type> il, const I &a) {}


    template < typename Ty, template <typename ...> typename Aggregation
//*    ,typename Compare , Allocator
    >
    std::string to_string(  const box<Ty, Aggregation
// *
    > & o, const std::string& boxon="{", const std::string& boxoff="} ", const std::string& delim=", " ) {

        struct vis {

            const std::string& _bxon;
            const std::string& _bxoff;
            const std::string& _delim;
            auto operator()(const Ty&a )const {
                std::ostringstream ost;
                ost<< a;
                return  ost.str();
            }
            auto operator()(const  Aggregation<  box<Ty, Aggregation
// *  ---agg_t?
            > >&o)const {
                std::ostringstream ost;
                ost<<_bxon;
                for (const auto&v : o) {
                    ost<<  to_string( v,_bxon, _bxoff,_delim )<<_delim ;
                }
                ost<<_bxoff<<' ';
                return    ost.str() ;
            }
        };

        return std::visit(vis{boxon,boxoff,delim}, o._value);
    }
    template < typename Ty, template <typename ...> typename Aggregation
            // *  ,class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty>>
    >
    std::string to_string(  const  typename box<Ty, Aggregation
            // *                       ,Compare,Allocator
    >::agg_t & o, const std::string& boxon="{", const std::string& boxoff="}; ", const std::string& delim=", " ) {
        std::ostringstream ost;
        ost<< "agg_t ("<<o.size()<<"){ ";
        for (const auto &e:o){
            ost<< to_string(e)<<"\n";
        }
        ost<<" }";
        return ost.str();
    }



}

#endif
