#pragma  once

#include <type_traits>
#include <list>
#include <vector>
#include <array>


namespace stepworks::detect
{
    
    namespace detail{
    
    // To allow ADL with custom begin/end
    using std::begin;
    using std::end;

    template <typename T>
    auto is_iterable_impl(int)
    -> decltype (
        begin(std::declval<T&>()) != end(std::declval<T&>()), // begin/end and operator !=
        void(), // Handle evil operator ,
        ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++        
        void(*begin(std::declval<T&>())), // operator*
        std::true_type{});

    template <typename T>
    std::false_type is_iterable_impl(...);
    
    
    template <typename T>
    auto is_iterable_ins1_impl(int)
    -> decltype (
        begin(std::declval<T&>()) != end(std::declval<T&>()), // begin/end and operator !=
        void(), // Handle evil operator ,
        ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
        std::declval<T&>().insert( std::declval< typename T::value_type>()  )         ,
        void(*begin(std::declval<T&>())), // operator*
        
        
         
        std::declval< typename T::value_compare>()  ,
        std::is_same < typename T::value_type, typename T::key_type  >   {}         
       //  std::true_type{}
    );
    
    template <typename T>
    std::false_type is_iterable_ins1_impl(...);
    
    
    template <typename T>
    auto is_iterable_kv_impl(int)
    -> decltype (
        begin(std::declval<T&>()) != end(std::declval<T&>()), // begin/end and operator !=
        void(), // Handle evil operator ,
        std::declval<T&>().at( std::declval< typename T::key_type>() )   ,
        ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
        std::declval<T&>().operator[]( std::declval< typename T::key_type>() )         ,
        void(*begin(std::declval<T&>())), // operator*
        std::true_type{});

    template <typename T>
    std::false_type is_iterable_kv_impl(...);
    
    template <typename T>
    auto is_iterable_push_impl(int)
    -> decltype (
        begin(std::declval<T&>()) != end(std::declval<T&>()), // begin/end and operator !=
        void(), // Handle evil operator ,
        ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
        std::declval<T&>().push_back( std::declval< typename T::value_type>()  )         ,
        void(*begin(std::declval<T&>())), // operator*
        std::true_type{});

    template <typename T>
    std::false_type is_iterable_push_impl(...);
    
    }
    
    template <typename T>
    using is_iterable = decltype( detail::is_iterable_impl<T>(0) );

    template <typename T>
    using is_iterable_ins1 = decltype( detail::is_iterable_ins1_impl<T>(0) );
    
    template <typename T>
    using is_iterable_kv = decltype(detail::is_iterable_kv_impl<T>(0));
    
    template <typename T>
    using is_iterable_pback = decltype(detail::is_iterable_push_impl<T>(0));

    /*
    template <typename T>    
    using is_iterable_fix = decltype( detail::is_iterable_impl<T>(0))::value 
                        && ! 
                            decltype(detail::is_iterable_ins1_impl<T>(0) )::value
//                        && ! decltype(detail::is_iterable_kv_impl<T>(0))::value
//                        && ! detail::is_iterable_push_impl<T>(0) 
                                     ;  // and decltype(!detail::is_iterable_impl<T>(0)) ;
     */                                    
}
