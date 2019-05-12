#pragma once

#include <apply.hpp>

namespace stepworks::wtype {
  ///@todo impl
    
/*
template <typename Ta>
auto _assign(Ta&& dest, const Ta& src ) {
    return std::move(dest)=src;
}

template <typename Ta>
auto _assign( std::list<Ta>&& dest, const Ta& src ) {
    std::move(dest).push_back(src);
    return std::move(dest);
}
*/


template <typename Key, typename Ta,  template<typename...>  typename Dest>
struct  assign {

    Dest<Key,  Ta>&& _dest;

    constexpr  Dest<Ta> f1( const Key& k, const Ta&a) const {
        _assign(  std::move( _dest)[k],  a )  ;
        return std::move(_dest);
    }

    constexpr  bool f0()const {
        return std::move( _dest);
    }

};

/*
template <typename Key, typename Ta,  template<typename...>  typename Dest, template <typename...> typename List>
struct  __assign2list {

    Dest<Key,  List<Ta>>  _dest;

    Dest<Key,List<Ta>> f1( std::pair<Key,Ta>kv)   {
        _assign(
            //std::move(std::move(
            std::move( _dest[kv.first]),  kv.second
        )  ;
        int t;
        {
            t= _dest.size();
        }
        return  std::move(_dest);
    }

    auto f0()const {
        return std::move(_dest);
    }

};
*/


template <typename Key, typename Ta,  template<typename...>  typename Dest, template <typename...> typename List>
struct  assign2list {

    Dest<Key,  List<Ta>>  _dest;

    Dest<Key,List<Ta>> f1( std::pair<Key,Ta>kv)
    {
        _dest[kv.first].push_back(kv.second);
        return  std::move(*this);
    }

    auto f0()const {
        return std::move(*this);
    }

};


using stepworks::application::_;

template<typename Key,   typename Ta,
         template<typename...>  typename Dest,
         template <typename > typename Form
         >
auto  _go_(assign<Key, Ta, Dest >&& dest, Form< std::pair<Key,Ta > >&& a_ )->assign<Key, Ta, Dest  > {
    Form<std::pair<Key,Ta>> a0 = std::move(a_);
    return
        apply (dest, a0);
    /*(
       
                 apply_optional_void<
               std::pair<Key,Ta>, Dest<Key,Ta>
               >( a0, assign<Key, Ta, Dest>(dest) ));
    */
}



template<typename Key,   typename Ta,
         template<typename...>  typename Dest,
         template <typename...> typename List,
         template <typename > typename Form
         >
auto  _go_ ( assign2list<Key, Ta, Dest,List >&& dest, Form< std::pair<Key,Ta > >&& a_ )->assign2list<Key, Ta, Dest,List  > {
    Form<std::pair<Key,Ta>> a0 = std::move(a_);
    return

    assign2list<Key, Ta, Dest,List  > {
        (  apply /*_optional_void*/<
         std::pair<Key,Ta>,
         Dest<Key,List< Ta> >    >( a0, //  assign2list<Key, Ta, Dest,List>(
                                    std::move( dest)
                                    // )

                                  )
        )
    };
}
/**/

}
