#pragma once
#include <type_traits>
//#include <experimental/c>

namespace stepworks::steph
{

//isfunctor =>  fmap


template< class, class = void>
struct is_function_object:  std::false_type {};



template <typename Fo>
struct is_function_object<Fo,
           std::void_t<
       decltype (
           std::declval<Fo>(). operator() ( std::declval< typename  Fo::arg_type>() ),
           std::declval< typename  Fo::ret_type>()
       )
       >         >
       :
       std::is_same <
       typename Fo::ret_type
       ,
       decltype (
           std::declval<Fo>(). operator() (
               std::declval< typename  Fo::arg_type>()
           )
       )

       >::type { //::value
       };

//////CONCEPT       
/*       
template <typename Fo>
concept FunctionObject = is_function_object<Fo>::value;
*/
/*
template <typename Fo, typename Ta, typename Tb>
concept Functor requires (FunctionObject fo){
*/    


//explicit generic, (dont 'using need arg_type...')
template< class, class = void>
struct is_function_object_t:  std::false_type {};


template <template< typename...> typename Fo, typename Ta>
struct is_function_object_t<Fo<Ta>,
           std::void_t<
       decltype (
           std::declval<Fo<Ta>>(). operator() (  std::declval< const Ta&>() ),
           std::declval< typename  Fo<Ta>::ret_type>()
       )
       >         >
       :
       std::is_same <
       typename Fo<Ta>::ret_type
       ,
       decltype (
           std::declval<Fo<Ta>>(). operator() (
               std::declval< const Ta &>()
           )
       )

       >::type { //::value
       };
       
template< class, class = void>
struct is_function_object0_t:  std::false_type {};


//Ta()
template < template<typename> typename Fo, typename Ta>
struct is_function_object0_t< 
              Fo<Ta>,
           std::void_t<
       decltype (
           std::declval<Fo<Ta>>(). operator() ( )
           
//           std::declval< Fo<Ta> >()()
       )
       >      
       >
       :
       std::is_same <
       Ta,
       
       decltype (
           std::declval<Fo>(). operator() (
           )
       )

       >::type {};
       
       
/*       
template <template <typename...> typename Fo, typename Ta>
concept FunctionObject_t = is_function_object_t<Fo<Ta>>::value;
*/       
       
///so ungefähr die Idee

/*

template <template<typename...>typename F, typename Ta>
concept Functor = requires( F<Ta> m, FunctionObject_t<Ta> fo){
    
    fmap(m, fo)->F< FunctionObject_t::res_type >;
}

*/
       
}



