//
// Created by kh on 18.01.21.
//

#ifndef STEPWORKS_DETECT_FA2BOX_HPP
#define STEPWORKS_DETECT_FA2BOX_HPP

#include <box/box.hpp>

using stepworks::bxx::box;

namespace stepworks::detect {

    /// F a->box<b,C>

    template<class, class, class, template<typename ...> class, class = void>
    struct is_function_a2box : std::false_type {
    };

    template<typename F, typename Ta, class Tb,
            template<typename...> typename  C>
    struct is_function_a2box<F,Ta,Tb,C,
            std::void_t <
            decltype(std::declval<F>().operator()(std::declval<Ta>()))
            >
    >
    : std::is_same
       <    box<Tb, C> ,
            decltype(std::declval<F>().operator()(std::declval<Ta>()))
       >
    ::type {};

///////////////////////

    /// F a,F&&-> box<b,C>,F    Functionobject is its own moving context

    template<class, class, class, template<typename ...> class, class = void>
    struct is_function_aF2boxF : std::false_type {
    };

    template<typename F, typename Ta, class Tb,
            template<typename...> typename  C>
    struct is_function_aF2boxF<F,Ta,Tb,C,
            std::void_t <
                    decltype(std::declval<F>().operator()(std::declval<Ta>(), std::move( std::declval<F>()  )   ))
            >
    >
            :// std::true_type {};
            std::is_same
                      <   std::pair<  box<Tb, C>, F> ,
                              decltype(std::declval<F>().operator()(std::declval<Ta>(),
                                      std::move( std::declval<F>()  )   ))
                      >
              ::type {};


    /// F a,C&&-> box<b,C>,C    Functionobject moving Context (extra )

    template<class, class, class, template<typename ...> class, class, class = void>
    struct is_function_aCx2boxCx : std::false_type {
    };

    template<typename F, typename Ta, class Tb,
            template<typename...> typename  C,
                    typename Cx>
    struct is_function_aCx2boxCx<F,Ta,Tb,C, Cx,
            std::void_t <
                    decltype(std::declval<F>().operator()(std::declval<Ta>(), std::move( std::declval<Cx>()  )   ))
            >
    >
//            :std::true_type {};
                 :  std::is_same
                            <   std::pair<  box<Tb, C>, Cx> ,
                                    decltype(std::declval<F>().operator()(std::declval<Ta>(),
                                                                          std::move( std::declval<Cx>()  )   ))
                            >
                    ::type {};



////////////////////

template<class, class, class, class, template<typename ...> class, class = void>
struct is_function_aCx2box : std::false_type {
};

template<typename F, typename Ta, class Tb, class Cx,
        template<typename...> typename  C>
struct is_function_aCx2box<F,Ta,Tb,Cx, C,
        std::void_t <
                decltype(std::declval<F>().operator()(std::declval<Ta>(), std::declval<Cx>() ))
        >
>
        : std::is_same
                  <    box<Tb, C> ,
                       decltype(std::declval<F>().operator()(std::declval<Ta>(), std::declval<Cx>() ))
                  >
          ::type {};

}

#endif //STEPWORKS_DETECT_FA2BOX_HPP
