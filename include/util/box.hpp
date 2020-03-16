#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <variant>
#include <initializer_list>


namespace stepworks::bx {
    

template <typename Ty, template <typename ...> typename Aggregation >
struct box {
    using type = std::variant< Ty,  Aggregation<   box<Ty, Aggregation> > >;
    using agg_t = Aggregation< box< Ty, Aggregation> >;
    using base_t =Ty;

    type _value;
    box(type&& v): _value (std::move(v)){     //   std::cout<<"-1-";
    }
    box(const type& a):_value(a){     // std::cout<<"-2-";
    }
    
    box( agg_t&& a):_value(std::move(a)){      //   std::cout<<"-3-";
    }
    box(std::initializer_list<       std::variant < Ty,             box<Ty,Aggregation>  >> il); 
};

namespace l2r{
    
    template <typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation>
    auto move_box(  box<Ty,LeftAggregation>&& l  )-> box<Ty,RightAggregation> ;
    
    template <typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation>
    auto move_box_value(  typename box<Ty,LeftAggregation>::type&& l  )-> typename box<Ty,RightAggregation>::type;
    
    template <typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation>
     auto move_elements(  
        typename box<Ty,LeftAggregation>::agg_t&& s ,typename box<Ty,RightAggregation>::agg_t&& d=typename box<Ty,RightAggregation>::agg_t{} )-> typename box<Ty,RightAggregation>::agg_t {
            
        for (auto&&e : s){
                std::move(d).push_back(   move_box<Ty,LeftAggregation,RightAggregation>( std::move(e))   );
        }
        return std::move(d);
    };
    

    template <typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation>
    auto move_box(  box<Ty,LeftAggregation>&& l  )-> box<Ty,RightAggregation> {
        return 
            move_box_value<Ty,LeftAggregation, RightAggregation>( std::move(l._value)  )   ;
    }
    
    template <typename Ty, template <typename...> typename LeftAggregation, template <typename ...> typename RightAggregation>
    auto move_box_value(  typename box<Ty,LeftAggregation>::type&& l  )-> typename box<Ty,RightAggregation>::type {
        
        struct  {
        auto operator()( Ty a )const {
            return   typename box<Ty,RightAggregation>::type{ std::move(a)  };
        }
        auto operator()(     LeftAggregation< box<Ty, LeftAggregation>  > a ) const {
          
            return   typename box<Ty,RightAggregation>::type{ move_elements<Ty, LeftAggregation, RightAggregation>(  std::move(a))};                           
        }   

        }vis;        
        return std::visit(vis, std::move(l));
    }
}


///case a    
template <typename Ty, template<typename...> typename Aggregation>
auto mk_box(Ty&& a )->  box<Ty,Aggregation> {
    return box<Ty,Aggregation> { std::forward<Ty>(a) };
}

template <typename Ty, template <typename ...> typename Aggregation >
std::string to_string(  const box<Ty, Aggregation> & o, const std::string& boxon="{", const std::string& boxoff="} ", const std::string& delim=", " ) {

    struct vis {

        const std::string& _bxon;
        const std::string& _bxoff;
        const std::string& _delim;
        auto operator()(const Ty&a )const {
            std::ostringstream ost;
            ost<< a;
            return  ost.str();
        }
        auto operator()(const  Aggregation<   box<Ty, Aggregation> >&o)const {
            std::ostringstream ost;
            ost<<_bxon;
            for (const auto& x: o) {
                ost<< to_string(x,_bxon, _bxoff,_delim )<<_delim;
            }
            ost<<_bxoff<<' ';
            return    ost.str() ;
        }
    };

    return std::visit(vis{boxon,boxoff,delim}, o._value);

}


namespace detailX {

template <typename Base, template <typename...> typename Aggregation, typename...Args>
auto append_args(Aggregation<  box< Base, Aggregation >  >&& agg, Args&&...args) {
    (std::move(agg).push_back(( box<Base,Aggregation>) {
        std::forward<Args>(args)
    }), ...);
    return  std::move(agg);
}
}

template <typename Base 
, template <typename...> typename Aggregation
>
auto mk_box_value(std::initializer_list<
       std::variant < Base,
             box<Base,Aggregation>  >> il   )-> typename box<Base,Aggregation>::type
{
    typename box<Base, Aggregation>::agg_t agg_dest; 
     
    struct  {
        auto operator()(  Base a ) const  {
            return  box<Base,Aggregation>( typename box<Base,Aggregation>::type( a) );
        }
        auto operator()(  box<Base,Aggregation>  a )const  {
            return   a; 
        }
         
        } vis;
        /*
        auto it = il.begin();
        while (it != il.end()){
            auto  el = std::move(*it++);
           */
        for ( auto&& el :   std::move(il)  ){
           agg_dest.push_back(   std::visit(vis, std::move( el) )
          );
        }
        return typename box<Base,Aggregation>::type{  agg_dest };
}

template <typename Base 
, template <typename...> typename Aggregation
>
auto mk_box(std::initializer_list<
       std::variant < Base,
             box<Base,Aggregation>  >>&& il   )//->box<Base,Aggregation>
{
    return box<Base,Aggregation>{   mk_box_value<Base,Aggregation>(  std::move(il) )  };
}


template <typename Ty , template <typename...> typename Aggregation>
   box<Ty, Aggregation>::box(std::initializer_list<       std::variant < Ty,             box<Ty,Aggregation>  >> il){
        _value =mk_box_value<Ty, Aggregation>(std::move(il));  
}


}

template <typename Ty, template<typename...> typename Aggregation>
auto operator<< (std::ostream s,  const stepworks::bx::box<Ty,Aggregation>& o){
    s << to_string(o);
    return s;
}

