//
// Created by kh on 16.01.21.
//
#pragma once
#include <type_traits>

#include <util/call.hpp>

using namespace stepworks::util::call;   ///MACRO in namespace

namespace  stepworks::amorph{



    template <typename  Ta, template<typename ...> typename C, typename Cx>
    using  Selh = auto(*) (const C<Ta> & c,  Cx&& context  )->std::pair<typename C<Ta>::const_iterator , Cx>;

    namespace detect{


        template<class , class=void>
                struct context_step_support: std::false_type {};

        template <typename Cx>
            struct context_step_support<Cx,
                    std::void_t<
                    decltype(std::declval<Cx>().step_option())
                    >
                    >:std::true_type{ };

        template< class, class, //class,
                class = void>
        struct context_is_selh : std::false_type {};

        template < typename Cx, typename  C>
        struct context_is_selh< Cx,C,
                std::void_t
                <
                    decltype(
                            std::declval<Cx>()
                    ( std::declval<C>(), std::move( std::declval<Cx>()) )
                    )
                >
        > :std::is_same<
                        decltype( std::declval<Cx>() ( std::declval<C>(), std::move( std::declval<Cx>()) ) ),
                        std::pair<typename C::const_iterator, Cx>
                >::type
        {};
    }


    template <typename  Ta, template<typename ...> typename C, typename Cx>
    auto select(const Selh<Ta, C,Cx>& sel,const C<Ta> & c,  Cx&& context  )
    {
        return  sel(c,  std::move(context));
    };

    ///context contains selector
    template <typename  Ta, template<typename ...> typename C, typename Cx>
    requires (detect::context_is_selh<  Cx, C<Ta> >::value)
    auto select(const C<Ta> & c,  Cx&& context_  )->std::pair<typename C<Ta>::const_iterator, Cx>
    {
        typedef std::pair<typename C<Ta>::const_iterator , Cx>  (Cx::*F)( const C<Ta>&, Cx&&  );
        auto context = std::move(context_);
        F sel=     &Cx::operator();
        assert(sel);
        return CALL_MEMBER_FN(context,sel)  (c,  std::move(context));
    };

}

