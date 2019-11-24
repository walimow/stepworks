
#pragma once
#include <type_traits>
#include <util/detect.hpp>

#include <optional>

namespace stepworks::steph
{

template <typename ...> struct fmapt;



//pure
template < typename Ft,  typename Ta         >
struct fmapt<Ft, Ta>
{
    Ft&& f;
    auto operator()( const Ta&  a)const {
        return  std::move( f) ( a );    // std::invoke<Ft,  int > (  f ,   a   );
    }
};


template < typename Ft,  typename Ta, typename K,template<typename...> typename Container>
struct fmapt<Ft, Container<K,Ta>
//,   std::void_t<stepworks::detect::is_iterable_kv <Container<K,Ta>>>
    >
{
    Ft&& f;
    typename std::enable_if<
    stepworks::detect::is_iterable_kv <Container<K,Ta>>::value,
              Container< K, decltype( std::declval<Ft>() ( std::declval<Ta>() ) )    > > ::type
    operator()( const Container< K,Ta>& c)const {
        using Tb = decltype(f( std::declval<Ta>() ));
        Container<K,Tb> res;
        for (const auto& [k,a]: c)
            res.insert( std::make_pair (  k, fmap(std::move( std::move( f) ),a) ) );
        return res;
    }
};


template < typename Ft,  typename Ta, size_t Sz>
struct fmapt<Ft, std::array<Ta,Sz>>
{
    Ft&& f;
    auto   operator()( const std::array<Ta,Sz>& c) const {
        using Tb = decltype(f( std::declval<Ta>() ));
        std::array<Tb,Sz> res;
        for ( std::size_t k=0; k < c.size(); k++)
            res[k]=   fmap( std::move(f), c[k]  );
        return res;
    }
};
/////////////

namespace detail {
    
template < typename Ft,  typename Ta, template<typename...> typename Container>
struct fmapt_ins
{

    Ft&& f;    
    auto operator()( const Container<Ta>& c)const {
        using Tb = decltype(f( std::declval<Ta>() ));
        Container<Tb> res;
        for (const auto& a: c)
            res.insert( fm(std::move( f),a) );
        return res;
    }
};



template < typename Ft,  typename Ta, template<typename...> typename Container>
struct fmapt_pb
{

    Ft&& f;
 /*   typename std::enable_if<
    stepworks::detect::is_iterable_pback < Container<Ta> >::value,
              Container< decltype( std::declval<Ft>() ( std::declval<Ta>())) > > ::type
              */
 auto
    operator()( const Container<Ta>& c)const {
        using Tb = decltype(f( std::declval<Ta>() ));
        Container<Tb> res;
        for (const auto& a: c)
            res.push_back( fm(std::move( f),a)   );
        return res;
    }
};


}

/////////////

//Pure
template <typename F, typename Ty>
auto fm( F&& f, const Ty& a ) {
    return fmapt<F,Ty> { std::move(f)}(a);
}

//set
template <typename F, typename Ta, template <typename ...> typename Container>

typename std::enable_if<
stepworks::detect::is_iterable_ins1 <Container<Ta>>::value,
          Container< decltype( std::declval<F>() ( std::declval<Ta>())) > > ::type

fm( F&& f, const Container<Ta>& a ) {
    return detail::fmapt_ins<F, Ta, Container> { std::move(f)}(a);
}
//vector
template <typename F, typename Ta, template <typename ...> typename Container>
typename std::enable_if<
stepworks::detect::is_iterable_pback <Container<Ta>>::value,
          Container< decltype( std::declval<F>() ( std::declval<Ta>())) > > ::type
fm( F&& f, const Container<Ta>& a ) {
    return detail::fmapt_pb<F,Ta, Container> { std::move(f)}(a);
}

//map
template <typename F, typename K, typename Ta, template <typename ...> typename Container>
typename std::enable_if<
stepworks::detect::is_iterable_kv <Container<K,Ta>>::value,
          Container< K, decltype( std::declval<F>() ( std::declval<Ta>() ) )    > > ::type
fm( F&& f, const Container<K,Ta>& a ) {
    return fmapt< F,Container<K, Ta> > { std::move(f)}(a);
}


template <typename F,  typename Ta>
auto fm( F&& f, const std::optional<Ta>& a ) {  
    using Tb =    decltype( std::declval<F>()   (     std::declval<Ta>()   )       );
    return (a) ? std::move(f)(*a) 
                : 
                 std::optional< Tb >{};
}






}
