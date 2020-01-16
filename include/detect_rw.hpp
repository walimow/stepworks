#pragma once

// context is just one type, if its  variadic (or any oher other combination), is has to be a tupe (or a struct)

namespace stepworks {

//reader without context
namespace r0 {

template< class, class = void>
struct is_reader_tR : std::false_type {};


template <class R>
struct is_reader_tR<R,
       std::void_t<            decltype(_(std::declval<R&&>()
                                         ))       >
       >
       :
       std::is_same <
       std::pair< R, typename R::element_type>
       ,
       decltype(
           _(std::declval<R&&>())
       )
       >::type
       { };
}



///reader with context
namespace rcx {
template<typename R, typename =void>  struct is_reader_tR : std::false_type {};


template <class R>
struct is_reader_tR<R,
           std::void_t<
       decltype(_ (
                    std::declval<R&&>(),
                    std::declval < const typename R::context_type&>()
                )  )  >
       >
       :

       std::is_same <
       std::pair< R, typename R::element_type>
       ,
       decltype(
           _  (std::declval<R&&>(), std::declval<const typename R::context_type& >()) 
       )
       >::type

       { };

}

///reader without context, returns framed reader R->(R),e
namespace r0x {

template< class, class = void>
struct is_reader_tR : std::false_type {};

template <class R>
struct is_reader_tR<R,
       std::void_t< decltype(
           _( std::declval<R&&>()   )
       )
       >
       >
       : std::is_same <

       std::pair<
       typename R::base_return_framed_type
       ,
       typename R::element_type
       >
       ,
       decltype(
           _(std::declval<R&&>())
       )

       >::type
       { };
}

///reader with context, returns framed reader
namespace rxcx {

template< class, class = void>
struct is_reader_tR : std::false_type {};

template <class R>
struct is_reader_tR<R,
       std::void_t< decltype(
           _( std::declval<R&&>(),
              std::declval < const typename R::context_type&>()
            )
       )
       >

       >
       : std::is_same <

       std::pair<
       typename R::base_return_framed_type
       ,
       typename R::element_type
       >
       ,
       decltype(
           _(std::declval<R&&>()
             , std::declval<const typename R::context_type& >()
            )
       )

       >::type
       { };
}

namespace w0 {

template< class, class = void>	struct is_writer_tR : std::false_type {};

template <class W>
struct is_writer_tR<W,
       std::void_t< decltype(_( std::declval<W&&>(),
                                std::declval<typename W::element_type&&>() )  )       >
       >
       :
       std::is_same <
       W
       ,
       decltype(_
                (
                    std::declval<W&&>(), std::declval<typename W::element_type&&>()
                )
               )

       >::type


       { };
}

namespace wx0 {

template< class, class = void>	struct is_writer_tR : std::false_type {};

template <class W>
struct is_writer_tR<W,
       std::void_t< decltype(_( std::declval<W&&>(),
                                std::declval<typename W::element_type&&>() )  )       >
       >
       :
       std::is_same <
       typename W::base_return_framed_type
       ,
       decltype(_
                (
                    std::declval<W&&>(), std::declval<typename W::element_type&&>()
                )
               )

       >::type
       { };
}



namespace wcx {

template< class,  class = void>
struct is_writer_tR : std::false_type {};

template <class W>
struct is_writer_tR<W,
       std::void_t<            decltype(_( std::declval<W&&>(),
                                        std::declval< typename W::element_type&&>(),
                                        std::declval < const typename W::context_type&>()
                                         )
                                       )
       >
       >
       :
       std::is_same <
       W
       ,
       decltype(_( std::declval<W&&>(),
                   std::declval< typename W::element_type&&>()
                   ,       std::declval < const typename W::context_type&>())
               )
       >::type
       { };
}

namespace wxcx {

template< class,  class = void>
struct is_writer_tR : std::false_type {};

/////////////////

template <class W>
struct is_writer_tR<W,
       std::void_t<            decltype(_( std::declval<W&&>(),
                                        std::declval< typename W::element_type&&>(),
                                        std::declval < const typename W::context_type&>())
                                       )
       >
       >
       : 
       std::is_same <
       typename W::base_return_framed_type
       ,
       decltype(_( std::declval<W&&>(),
                   std::declval< typename W::element_type&&>()
                   ,       std::declval < const typename W::context_type&>())
               )
       >::type       
       { };
}

}
