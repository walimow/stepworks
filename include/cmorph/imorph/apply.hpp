//
// Created by kh on 14.01.21.
//

#pragma once

#include <utility>
#include <detect/detect_cmorph.hpp>

/// imorph : ~>same size  pos[a] <> pos[b]

namespace  stepworks::imorph{

    ///simple , size(d) type(no allocator!)
    template <typename Ta, typename Faa, template <typename...> typename  Cs, typename Tb = decltype( std::declval<Faa>()(std::declval<Ta>())  )>
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            && stepworks::detect::supports_const_size<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Tb>::value   //redundand in default...
            &&  stepworks::detect::supports_set_ix_value<Cs<Ta>>::value
    )

    static auto apply( const Cs<Ta>& src, const Faa& faa){
               auto sz  = src.size();
               using dest_t = decltype(  faa  (std::declval<Ta>()));
               auto dest = Cs< dest_t>(sz);
               for (std::size_t k=0; k < sz;k++)
                   dest[k]= faa(src[k]);
               return dest;
        }

    ///simple , size(d) type( allocator!)
    template <typename Ta, typename Faa, template <typename...> typename  Cs, typename  Alloc, typename Tb = decltype( std::declval<Faa>()(std::declval<Ta>())  )>
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            && stepworks::detect::supports_const_size<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Tb>::value   //redundand in default...
            &&  stepworks::detect::supports_set_ix_value<Cs<Ta>>::value
    )

    static auto apply( const Cs<Ta>& src, const Faa& faa,  Alloc&alloc  ){
        auto sz  = src.size();
        using dest_t = decltype(  faa  (std::declval<Ta>()));
        auto dest = Cs< dest_t>(  sz, alloc);
        for (std::size_t k=0; k < sz;k++)
            dest[k]= faa(src[k]);
        return dest;
    }

    template <typename Ta, typename Faa, template <typename...> typename  Cs, template <typename...> typename  Cd,
    typename Tb = decltype( std::declval<Faa>()(std::declval<Ta>())  )
    >
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            && stepworks::detect::supports_const_size<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Tb>::value
            &&  stepworks::detect::supports_set_ix_value<Cs<Ta>>::value
            &&  stepworks::detect::supports_resize<Cd<Tb>>::value
    )
    static auto apply( const Cs<Ta>& src, Cd<Tb>&& d, const Faa& faa){
        auto sz  = src.size();
        auto dest = std::move(d);
        dest.resize(sz);
        for (std::size_t k=0; k < sz;k++)
            dest[k]= faa(src[k]);
        return dest;
    }

    /// push_back , but no resizes( list)

    template <typename Ta, typename Faa, template <typename...> typename  Cs, template <typename...> typename  Cd,
            typename Tb = decltype( std::declval<Faa>()(std::declval<Ta>())  )
    >
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            && stepworks::detect::supports_const_size<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Ta>::value
            &&  !stepworks::detect::supports_set_ix_value<Cs<Ta>>::value
            &&  !stepworks::detect::supports_resize<Cd<Tb>>::value
            &&  stepworks::detect::supports_push_bak<Cd<Tb>>::value
    )
    static auto apply( const Cs<Ta>& src, Cd<Tb>&& d, const Faa& faa){
        auto sz  = src.size();
        auto dest = std::move(d);
        for (std::size_t k=0; k < sz;k++)
            dest.push_back( faa(src[k]));
        return dest;
    }

    ///quasi-imorph dests with insert (set )   --- container identity may effect skips

    template <typename Ta, typename Faa, template <typename...> typename  Cs, template <typename...> typename  Cd,
            typename Tb = decltype( std::declval<Faa>()(std::declval<Ta>())  )
    >
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            && stepworks::detect::supports_const_size<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Ta>::value
            &&  !stepworks::detect::supports_set_ix_value<Cs<Ta>>::value
            &&  !stepworks::detect::supports_push_bak<Cd<Tb>>::value
            &&  stepworks::detect::supports_insert<Cd<Tb>>::value
    )
    static auto apply( const Cs<Ta>& src, Cd<Tb>&& d, const Faa& faa){
        auto sz  = src.size();
        auto dest = std::move(d);
        for ( const auto&a: src )
            dest.insert( faa(a));
        return dest;
    }


    template <typename Ta, typename Faa, template <typename...> typename  Cs, template <typename...> typename  Cd,
            typename Tb = decltype( std::declval<Faa>()(std::declval<Ta>())  )
    >
    requires (
            stepworks::detect::has_size<Cs<Ta>>::value
            && stepworks::detect::supports_const_size<Cs<Ta>>::value
            &&  stepworks::detect::is_foab<Faa, Ta,Ta>::value
            //&&  !stepworks::detect::supports_resize<Cd<Tb>>::value
            //&&  !stepworks::detect::supports_push_bak<Cd<Tb>>::value
            &&  stepworks::detect::supports_insert<Cd<Tb>>::value
    )
    static auto apply_value( const Cs<Ta>& src, Cd<Tb>&& d, const Faa& faa=[](const Ta&a){return a;}){
        auto sz  = src.size();
        auto dest = std::move(d);
        for (const auto& [_,a]: src)
            dest.insert( faa(a));
        return dest;
    }



}