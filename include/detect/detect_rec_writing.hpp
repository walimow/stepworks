//
// Created by karsten on 16.11.20.
//

#ifndef STEPWORKS_DETECT_REC_WRITING_HPP
#define STEPWORKS_DETECT_REC_WRITING_HPP

#include <type_traits>
#include <utility>
#include <concepts>

/// receptor writing types: an abadonding aggregate object reproduced with an added element
/// there are different forms

namespace stepworks {


    ///the container writer/concept supports a method add_element(C&& , Ty)->C   (with implicit direction. Will work with list , vectors, deque etc )

    template<typename Ty, typename C, typename=void>
    struct has_append : std::false_type {
    };

    ///supports emplace_back
    template<typename Ty, typename C>
    struct has_append<Ty, C,
            std::void_t<
                    decltype(
                    std::declval<C>()
                            .emplace_back(std::declval<Ty>())
                    )
            >
    >
        /*    : std::is_same         <   C,
                        decltype(std::declval<Ty>().emplace_back(std::declval< Ty>()))
                >::type {};
                */
            : std::true_type {
    };

    template<typename Ty, typename C>
    concept Appendable= has_append<Ty, C>::value;

    template<typename C, typename=void>
    struct has_emplace_back : std::false_type {
    };

    template<typename C>
    struct has_emplace_back<C,
            std::void_t<
                    decltype(
                    std::declval<C>()
                            .emplace_back(std::declval<typename C::value_type>())
                    )
            >
    > : std::true_type {
    };

    template<typename C>
    concept EmplaceableR= has_emplace_back<C>::value;


    template<typename Ty, typename C, typename=void>
    struct has_append_front : std::false_type {
    };

    ///supports emplace_front
    template<typename Ty, typename C>
    struct has_append_front<Ty, C,
            std::void_t<
                    decltype(
                    std::declval<C>()
                            .emplace_front(std::declval<Ty>())
                    )
            >
    > : std::true_type
        /*std::is_same
                  <   C,
                          decltype(std::declval<Ty>().emplace_front(std::declval< Ty>()))
                  >::type */ {
    };

    template<typename Ty, typename C>
    concept EmplaceableL= has_append_front<Ty, C>::value;


    template<typename C, typename Ty, typename Context, typename=void>
    struct has_atref : std::false_type {
    };

    ///supports [at]  (vector, array...)
    template<typename C, typename Ty, typename Context>
    struct has_atref<Ty, C, Context,
            std::void_t<
                    decltype(
                    std::declval<C>()
                            .operator[](std::declval<Context>())
                    )
            >
    >
            :

            std::is_same<
                    decltype(std::declval<Ty>()) &,
                    decltype(std::declval<C>()[std::declval<Context>()])
            >::type {

        //    std::true_type {
    };


    template<typename Ty, typename C, typename Context>
    concept AtRefeByIndex= has_atref<Ty, C, Context>::value;


    template<typename C, typename =void>
    struct has_kvref : std::false_type {
    };

    template<typename C>
    struct has_kvref<C,
            std::void_t<
                    decltype(
                    std::declval<C>()
                            .operator[](std::declval<typename C::key_type>())
                    )
            >
    >
         : std::is_same<
                    //decltype( std::declval<typename C::value_type>() )

                    typename C::mapped_type,
                    typename std::decay<
                            decltype(std::declval<C>()[std::declval<typename C::key_type>()])
                    >::type
            >::type {
 //: std::true_type{
    };


    template<typename C>
    //concept  KvRef= has_kvref< typename C::value_type ,C, typename C::key_type>::value;

    concept KeyValueRef= has_kvref<C>::value;

    template<typename C>
    concept IxRef= has_atref<C, typename C::value_type, std::size_t>::value &&
                   !has_kvref<C>::value;  /// NO EXPLICIT key_type



    template<typename C, typename Ty, typename=void>
    struct has_insert : std::false_type {
    };

    ///supports [at]  (vector, array...)
    template<typename C, typename Ty>
    struct has_insert<Ty, C,
            std::void_t<
                    decltype(
                    std::declval<C>()
                            .insert(std::declval<Ty>())
                    )
            >
    > : std::true_type {
    };

    template<typename Ty, typename C>
    concept Insertable= has_insert<Ty, C>::value;



    ///////////// WRITING

    template<typename Ty, typename C, typename=void>
    struct is_writing : std::false_type {
    };

    template<typename Ty, typename C>
    struct is_writing<Ty, C,
            std::void_t<
                    decltype(

                    writing(
                            std::move(
                                    std::declval<C>()
                            ), std::declval<Ty>()
                    )
                    )
            > >
            : std::is_same
                      <C,
                              decltype(writing(std::move(std::declval<C>()), std::declval<Ty>()))
                      >::type {
    };
};


#endif //STEPWORKS_DETECT_REC_WRITING_HPP
