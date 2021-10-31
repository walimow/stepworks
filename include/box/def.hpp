//
// Created by karsten on 24.11.20.
//

#ifndef BOX_DEF_HPP
#define BOX_DEF_HPP

#include <variant>
#include <detect/detect_allocator.hpp>
#include <ostream>

using stepworks::detect::has_allocator;

namespace stepworks::bxx{

   // template <typename ...> struct box;

    template <typename Ty, template<typename ...> typename Aggregation>
    struct box{

        using base_t = Ty;
        using agg_t = Aggregation<box<base_t, Aggregation> >;
        using type = std::variant<Ty, agg_t>;

        using type_enum=enum{eatom=0, eaggregate=1};

        struct agg_position{
            const agg_t& _container;
            typename agg_t::const_iterator _it;
        };

        type _value;

        box(type v) : _value(std::forward<type>(v)) {     //   std::cout<<"-1-";
        }

     //   using is_allocable_container = typename has_allocator<typename box<Ty, Aggregation>::agg_t>::type;

        box(agg_t&& a) : _value(std::move(a)) {      //   std::cout<<"-3-";
        }

        box(const agg_t& a) : _value(a) {      //   std::cout<<"-3-";
        }

        box() {
            _value=agg_t {};
        }

        box(std::initializer_list< //std::variant<Ty,
                typename   box<Ty, Aggregation>::type  > il);

        template<typename B =  typename  box<Ty,std::initializer_list>::type, typename =     typename std::enable_if_t
                <
                       ! std::is_same<B, type>::value>::type>

        box( const  B& b ){
            _value=b;
        }

        template<typename I = const typename box<Ty, Aggregation>::agg_t, typename =     typename std::enable_if_t
                <  has_allocator<I>::value> >
        box(
                std::initializer_list<
                        typename box<Ty, Aggregation>::type> il, const I &a
        );

        box(type_enum  e) {
            _value= (e) ? type (agg_t {}) : type(base_t{});
        }

        operator type () const{
            return _value;
        }
/*
        bool operator==( const typename box<Ty,Aggregation>::type& other)const{
            struct {
                auto operator()(const Ty& la, const Ty&ra) const   {return la == ra;};
                auto operator()(const Ty& la, const typename box<Ty,Aggregation>::agg_t& rc ) const   {return false;};
                auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const Ty& ra )  const  {return false;};
                auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const typename box<Ty,Aggregation>::agg_t& rc )  const {
                    const auto itl = lc.cbegin();
                    const auto itr = rc.cbegin();
                    while(itl!= lc.cend() && itr!= rc.cend()){
                        if ( !eq(*itl , *itr)){
                            return false;
                        }
                    }
                    return true;
                };
            } vis;
            return std::visit( vis,_value,other);
        }

       inline bool operator==( const box<Ty,Aggregation>& other)const{
            return _value==other._value;
        }

        std::strong_ordering operator<=>(const  typename box<Ty,Aggregation>::type& other) const {
                struct {
                    auto operator()(const Ty& la, const Ty&ra)  const  {return la <=> ra;};
                    auto operator()(const Ty& la, const typename box<Ty,Aggregation>::agg_t& rc ) const   {
                        return rc.size()>0 ? false :  true ;};
                    auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const Ty& ra )const    {
                        return lc.size()==0 ?  true : false  ;};
                    auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const typename box<Ty,Aggregation>::agg_t& rc ) const ->std::strong_ordering {
                        const auto itl = lc.cbegin();
                        const auto itr = rc.cbegin();
                        while(itl!= lc.cend() && itr!= rc.cend()){
                            if ( !eq(*itl,*itr))
                                return *itl < itr->_value;
                        }
                        return itl== lc.cend()  ? itr==rc.cend() ? false :true
                        : false //itr==rc.cend() ?  std::strong_ordering::equal : std::strong_ordering::greater;
                        ;
                    };
                } vis;
                return std::visit( vis,_value,other);

        }

        bool operator<(const  typename box<Ty,Aggregation>::type& other) const {
            struct {
                auto operator()(const Ty& la, const Ty&ra)  const  {return la < ra;};
                auto operator()(const Ty& la, const typename box<Ty,Aggregation>::agg_t& rc ) const   {
                    return rc.size()>0 ?  std::strong_ordering::greater :  std::strong_ordering::less ;};
                auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const Ty& ra )const    {
                    return lc.size()==0 ?  std::strong_ordering::less : std::strong_ordering::greater  ;};
                auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const typename box<Ty,Aggregation>::agg_t& rc ) const ->std::strong_ordering {
                    const auto itl = lc.cbegin();
                    const auto itr = rc.cbegin();
                    while(itl!= lc.cend() && itr!= rc.cend()){
                        if ( !eq(*itl,*itr))
                            return itl->operator<=>( itr->_value);
                    }
                    return itl== lc.cend()  ? itr==rc.cend() ?  std::strong_ordering::equal :std::strong_ordering::less
                    :  itr==rc.cend() ?  std::strong_ordering::equal : std::strong_ordering::greater;
                    ;
                };
            } vis;
            return std::visit( vis,_value,other);

        }
*/
        inline std::weak_ordering operator<=>(const box<Ty,Aggregation>& other) const {
/*
            struct {
                auto operator()(const Ty& la, const Ty&ra)  const  {return la <=> ra;};
                auto operator()(const Ty& la, const typename box<Ty,Aggregation>::agg_t& rc ) const   {
                    return rc.size()>0 ? std::strong_ordering::less : std::strong_ordering::greater;};
                auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const Ty& ra )const    {
                    return lc.size()==0 ? std::strong_ordering::greater :  std::strong_ordering::less ;};
                auto operator()(const typename box<Ty,Aggregation>::agg_t& lc, const typename box<Ty,Aggregation>::agg_t& rc ) const ->std::strong_ordering {
                    const auto itl = lc.cbegin();
                    const auto itr = rc.cbegin();
                    while(itl!= lc.cend() && itr!= rc.cend()){
                        if ( *itl !=*itr)
                            return itl->_value < itr->_value ? std::strong_ordering::less : std::strong_ordering::greater ;
                    }
                    return itl== lc.cend()  ? itr==rc.cend() ? std::strong_ordering::equal  : std::strong_ordering::less
                    : std::strong_ordering::greater //itr==rc.cend() ?  std::strong_ordering::equal : std::strong_ordering::greater;
                    ;
                };
            } vis;
            return std::visit( vis,_value,other._value);
*/
            return _value<=>other._value;
        }

        friend std::ostream& operator <<   (std::ostream& s, const box<Ty, Aggregation>& o){
            s << to_string(o);
            return s;
        };
    };


    }





#endif //BOX_DEF_HPP
