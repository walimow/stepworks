//
// Created by kh on 11.04.20.
//

#ifndef STEPWORKS_BOXM_HPP
#define STEPWORKS_BOXM_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <variant>
#include <initializer_list>

///box for map (and maplike k:v-types)

namespace stepworks::bxm {


    template <typename K, typename Ty, template <typename ...> typename Aggregation=std::map
          ,class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty> >
            >
    struct boxm {
        using key_t  = K;
        using agg_t = Aggregation<K,  boxm< K, Ty, Aggregation>
        // *, Compare, Allocator
        >;
        using atom_t = Ty;
        using type =   std::variant< atom_t, agg_t >;
       // *  using alloc_t = Allocator;

        using base_t =Ty;

        type _value=agg_t {};
        boxm(type&& v): _value (std::move(v)){     //   std::cout<<"-1-";
        }
        boxm(const type& a):_value(a){     // std::cout<<"-2-";
        }

        boxm( const agg_t& a):_value(a){      //   std::cout<<"-3-";
        }

        boxm(){
            _value=agg_t{} ;
        }
        boxm(std::initializer_list<   std::pair<K,   std::variant < Ty,             boxm<K,Ty,Aggregation
             // * ,Compare,Allocator
             >  >>> il);

    };

    template <typename K, typename Ty, template <typename ...> typename Aggregation=std::map
      //*      ,class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty> >
    >
    static  constexpr unsigned char bx_dim( const boxm<K,Ty,Aggregation
        // *                                    ,Compare,Allocator
                                            > v){
        return  v._value.index();
    }

    template <typename K, typename Ty, template <typename ...> typename Aggregation=std::map
     // *       ,class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty> >
    >
    static  constexpr size_t bx_size( const boxm<K,Ty,Aggregation
       // *                               ,Compare,Allocator
                                      > &v){
        struct{
            auto operator()(const Ty&a )const {
                return  1;
            }
            auto operator()(const  Aggregation<   boxm<K,Ty, Aggregation
      // *              ,Compare,Allocator
       > >&o)const {
                return o.size();
            }
        }vis;
        return std::visit(vis, std::move(v));;
    }


    namespace l2r{

        template <typename K, typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation
  // *              ,class Compare = std::less<K>, typename AllocatorL = std::allocator<std::pair<const K, Ty> >, typename AllocatorR=AllocatorL
        >
        auto move_box(  boxm<K,Ty,LeftAggregation
  // *                      ,Compare,AllocatorL
                        >&& l  )-> boxm<K,Ty,RightAggregation
  // *                      ,Compare,AllocatorR
            > ;

        template <typename K, typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation
 // *               ,class Compare = std::less<K>, typename AllocatorL = std::allocator<std::pair<const K, Ty> >, typename AllocatorR=AllocatorL
        >
        auto move_box_value(  typename boxm<K,Ty,LeftAggregation
  // *                            ,Compare,AllocatorL
                              >::type&& l  )-> typename boxm<K,Ty,RightAggregation
  // *                            ,Compare,AllocatorR
                              >::type;

        template <typename K, typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation
  // *              ,class Compare = std::less<K>, typename AllocatorL = std::allocator<std::pair<const K, Ty> >, typename AllocatorR=AllocatorL
        >
        auto move_elements(
                typename boxm<K,Ty,LeftAggregation
  // *              ,Compare,AllocatorL
                >::agg_t&& s ,typename boxm<K,Ty,RightAggregation
                // *              ,Compare,AllocatorR
                >::agg_t&& d=typename boxm<K,Ty,RightAggregation
                // *               ,Compare,AllocatorR
                >::agg_t{} )-> typename boxm<K,Ty,RightAggregation
                // *            ,Compare,AllocatorR
                >::agg_t {

            for (auto&&e : s){
                std::move(d).push_back(   move_box<K,Ty,LeftAggregation,RightAggregation>( std::move(e))   );
            }
            return std::move(d);
        };


        template <typename K, typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation
                // *              ,class Compare = std::less<K>, typename AllocatorL = std::allocator<std::pair<const K, Ty> >, typename AllocatorR=AllocatorL
        >
        auto move_box(  boxm<K,Ty,LeftAggregation
                // *                    ,Compare,AllocatorL
                        >&& l  )-> boxm<K,Ty,RightAggregation
                // *         ,Compare,AllocatorR
                        > {
            return
                    move_box_value<Ty,LeftAggregation, RightAggregation
                            // *               ,Compare,AllocatorL,AllocatorR
                    >( std::move(l._value)  )   ;
        }

        template <typename K, typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation
                // *            ,class Compare = std::less<K>, typename AllocatorL = std::allocator<std::pair<const K, Ty> >, typename AllocatorR=AllocatorL
        >
        auto move_box_value(  typename boxm<K,Ty,LeftAggregation
                // *                  ,Compare,AllocatorL
                              >::type&& l  )-> typename boxm<K,Ty,RightAggregation
                // *              ,Compare,AllocatorR
                              >::type {

            struct  {
                auto operator()( Ty a )const {
                    return   typename boxm<K,Ty,RightAggregation
                            // *           ,Compare,AllocatorR
                    >::type{ std::move(a)  };
                }
                auto operator()(     LeftAggregation< boxm<K,Ty, LeftAggregation
                        // *                     ,Compare,AllocatorL
                        >  > a ) const {

                    return   typename boxm<K,Ty,RightAggregation
                            // *                   ,Compare,AllocatorR
                    >::type{ move_elements<Ty, LeftAggregation, RightAggregation
                            // *                        , Compare,AllocatorL,AllocatorR
                             >(  std::move(a))};
                }

            }vis;
            return std::visit(vis, std::move(l));
        }
    }


///case a    
    template <typename K, typename Ty, template<typename...> typename Aggregation
            // *       ,  class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty>>
                    >
    auto mk_box(const Ty a )->  boxm<K,Ty,Aggregation
            // *   ,Compare,Allocator
    > {
            auto ret = boxm<K,Ty,Aggregation
// *            ,Compare,Allocator
            > { a };
            return ret;
    }


    template <typename K, typename Ty, template <typename ...> typename Aggregation
//*    ,typename Compare , Allocator
            >
    std::string to_string(  const boxm<K,Ty, Aggregation
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
            auto operator()(const  Aggregation< K,  boxm<K,Ty, Aggregation
// *  ---agg_t?
            > >&o)const {
                std::ostringstream ost;
                ost<<_bxon;
                for (const auto&[k,v] : o) {
                    ost<< k << " > " << to_string( v,_bxon, _bxoff,_delim )<<_delim ;
                }
                ost<<_bxoff<<' ';
                return    ost.str() ;
            }
        };

        return std::visit(vis{boxon,boxoff,delim}, o._value);
    }
    template <typename K, typename Ty, template <typename ...> typename Aggregation
            // *  ,class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty>>
            >
    std::string to_string(  const  typename boxm<K,Ty, Aggregation
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


    namespace detailX {

        template <typename K, typename Base, template <typename...> typename Aggregation, typename...Args>
        auto append_args(Aggregation<  boxm< K,Base, Aggregation >  >&& agg, Args&&...args) {
            (std::move(agg).push_back(( boxm<K,Base,Aggregation>) {
                    std::forward<Args>(args)
            }), ...);
            return  std::move(agg);
        }
    }

    template <typename K, typename Base

            , template <typename...> typename Aggregation=std::map
    >
    auto mk_box_value(std::initializer_list<
       std::pair<K,
       std::variant < Base,
                            boxm<K, Base,Aggregation>  >>> il   )-> typename boxm<K,Base,Aggregation>::type
    {
        typename boxm<K,Base, Aggregation>::agg_t agg_dest;

        struct  {
            auto operator()(  Base a ) const  {
                return  boxm<K,Base,Aggregation>( typename boxm<K,Base,Aggregation>::type( a) );
            }
            auto operator()(  boxm<K,Base,Aggregation>  a )const  {
                return   a;
            }

        } vis;

        for ( auto&&[ k,el] :   std::move(il)  ){
            agg_dest[k]=(   std::visit(vis, std::move( el) )
            );
        }
        return typename boxm<K,Base,Aggregation>::type{  agg_dest };
    }

    template <typename K, typename Base
            , template <typename...> typename Aggregation
    >
    auto mk_box(std::initializer_list<
                std::pair<K,
                std::variant < Base,
                        boxm<K,Base,Aggregation>  >>> il   )//->box<Base,Aggregation>
    {
        //return boxm<K,Base,Aggregation>{   mk_box_value<K,Base,Aggregation>(  std::move(il) )  };
     //    typename boxm<K,Base,Aggregation>::agg_t x{il};
        return boxm<K,Base,Aggregation>(                il        )  ;
    }


    template <typename K, typename Ty , template <typename...> typename Aggregation
             , class Compare
                      /*= std::less<K>*/, typename Allocator /* = std::allocator<std::pair<const K, Ty>>*/
            >
    boxm<K,Ty, Aggregation
     ,Compare,Allocator
    >::boxm//<K,Ty, Aggregation>
         (std::initializer_list<  std::pair< K   ,
                 std::variant < Ty,       boxm<K,Ty,Aggregation
                         // *             , Compare,Allocator
                 >  >>> il){
        agg_t a;
        struct vis{
            agg_t&& a;
            K&& k;
            auto operator()( Ty&& v )const {
                a[k]= boxm(v);
                return std::move(a);
            }
            auto operator()(  boxm<K,Ty,Aggregation
                    // *   ,              Compare,Allocator
                    > &&  v )const {
                a[k]= boxm(v);
                return std::move(a);
            };
        };

        for (auto[k, v]: il) {
           a = std::visit(vis{std::move(a), std::move(k)}, std::move(v));
        }
        _value = a;
    }

}


template <typename K, typename Ty, template<typename...> typename Aggregation>
auto operator<< (std::ostream s,  const stepworks::bxm::boxm<K,Ty,Aggregation>& o){
    s << to_string(o);
    return s;
}



#endif //STEPWORKS_BOXM_HPP
