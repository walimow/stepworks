#pragma once


#include  <type_traits>
#include <utility>
    
template< typename...>
struct is_reader_t:  std::false_type{};

constexpr void _ (){} //invalid

//reader, 
template <class R>
struct is_reader_t<R, std::void_t<
    typename  std::is_same < 
                   std::pair< R, typename R::element_type>
                    , 
                   typename std::result_of
                    <
                        decltype( _ )&
                        ( R&& ) 
                    >::type
                        >::type
> >:std::true_type{ };



//reader, 
template <typename R, typename ...Context>
struct is_reader_t<R, std::void_t<
    typename  std::is_same < 
                   std::pair< R, typename R::element_type>
                    , 
                   typename std::result_of
                    <
                        decltype( _ )&
                        ( R&&, const Context&... ) 
                    >::type
                        >::type
>, Context... >:std::true_type{ };



/////////////////

template< class , class =void>
struct is_reader_tR:  std::false_type{};

///////////////// 

template <class R>
struct is_reader_tR<R, std::void_t<
    typename  std::is_same < 
                   std::pair< R, typename R::element_type>
               
                 //typename R::element_type
                    , 
                   typename std::result_of
                    <
                        decltype( _ )&
                        ( R&& ) 
                    >::type
                        >::type

> >:std::true_type{ };

/////////////////



template< typename ...> 
struct is_writer_t:  std::false_type{};

template <class W>
struct is_writer_t<W, std::void_t<
    typename  std::is_same < 
                   W
               
                    , 
                   typename std::result_of
                    <
                        decltype( _ )&
                        ( W&& , typename W::write_type) 
                    >::type
                        >::type

> >:std::true_type{ };


template <typename W, typename ...Context>
struct is_writer_t<W, std::void_t<
    typename  std::is_same < 
                   W
                    , 
                   typename std::result_of
                    <
                        decltype( _ )&
                        ( W&& , typename W::write_type&&, const Context&...) 
                        
                    >::type
                        >::type

> 
,Context...
>:std::true_type{ };



/*

template< class , class =void>
struct is_writer_tr:  std::false_type{};

//writer
template <class W>
struct is_writer_tr<W, std::void_t<
    typename  std::is_same < 
                   W
               
                    , 
                   typename std::result_of
                    <
                        decltype( _ )&
                        ( W&& , typename W::write_type) 
                    >::type
                        >::type

> >:std::true_type{ };
*/


    
//}
