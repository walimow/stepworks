#pragma once


#include <foab.first/isvalid.hpp>
//#include <xtypes.hpp>
#include <core/optional_type.hpp>
#include <core/optional.hpp>

#include <foab_fab.hpp>
#include <fab.hpp>
#include <apply.hpp>

//#include <foab_rrb.hpp>  //(a) ,b&&->b (optional a)


#include <ostream>
//#include <iostream>

using stepworks::types::var_t;

namespace stepworks
{

template <typename Ta,
          typename Stream = std::ostream,
          template <typename > typename Form = var_t>
struct wstream {

    struct wfoab {
        Stream&&  _dest;
        using _argument_type=Ta;
        wstream operator () ( const Ta& a ) const
        {
            std::move ( _dest )<<a;
            return wstream {std::move ( _dest ) };
        }
        wstream f0 () const
        {
            return wstream {std::move ( _dest ) };
        }
    };
    
    struct wfoab_pred {
        Stream&&  _dest;
        bool (*predicate)(const Ta&);
        using _argument_type=Ta;
        wstream operator () ( const Ta& a ) const
        {
            if (predicate(a))
                std::move ( _dest )<<a;
            return wstream {std::move ( _dest ) };
        }
        wstream f0 () const
        {
            return wstream {std::move ( _dest ) };
        }
    };


    Stream&& _stream;
    std::string _post;

    operator bool() const
    {
        return ! _stream.eof() && _stream.good();    //?
    }
    
    auto operator()(const Ta& a)const{
             std::move ( _stream )<<a;
            return wstream {std::move ( _stream ) };
    }

};



template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form = var_t
         >
auto  _go_ ( wstream<Ta, Src,Form >&& src, const Form<Ta>& a0 )->wstream<Ta,Src,Form>
{

    wstream<Ta, Src > s =std::move ( src );

    if ( s ) {
        return  stepworks::application::_ ( s ) ( a0 );

    }
    return   std::move ( s ) ;
}


template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form = var_t
         >
auto  _go_ ( wstream<Ta, Src,Form >&& src, const Form<Ta>& a0, bool ( *predicate ) ( const Ta& ) )->wstream<Ta,Src,Form>
{

    wstream<Ta, Src > s =std::move ( src );

    if ( s ) {
        return  stepworks::application::_ ( s,predicate ) ( a0 );
    }
    return   std::move ( s ) ;
}

template<typename Ta,
         typename  Src = std:: istream
         >
auto  _go_ ( wstream<Ta, Src, var_t >&& src, const var_t<Ta>& a0 )->wstream<Ta,Src,var_t>
{
   // typename wstream<Ta, Src, var_t>::wfoab o{std::move ( s )};
    //wstream<Ta, Src,var_t > s =std::move ( src );
    wstream<Ta, Src > s =std::move ( src );
    if ( s ) {
      
        return stepworks::application::_ (typename wstream<Ta, Src, var_t>::wfoab{std::move( src._stream) })  ( a0 );
    }
    return   std::move ( s ) ;
}


template<typename Ta,
         typename  Src = std:: istream
         >
auto  _go_ ( wstream<Ta, Src, var_t >&& src, const var_t<Ta>& a0, bool ( *predicate ) ( const Ta& ) )->wstream<Ta,Src,var_t>
{
    wstream<Ta, Src,var_t > s =std::move ( src );
    if ( s ) {
        //return  stepworks::application::_ ( s, predicate ) ( a0 );
        return stepworks::application::_ (typename wstream<Ta, Src, var_t>::wfoab_pred{std::move( src._stream), predicate })  ( a0 );
    }
    return   std::move ( s ) ;
}

template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form
         >
auto  _go_ ( wstream<Ta, Src, Form  >&& src, Ta&& a )
{
    wstream<Ta, Src, Form > s =std::move ( src );
    if ( s )
        s._stream<<a;
    return   std::move ( s ) ;
}


template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form
         >
auto  _go_ ( wstream<Ta, Src, Form  >&& src, Ta&& a, bool ( *predicate ) ( const Ta& ) )
{
    wstream<Ta, Src, Form > s =std::move ( src );
    if ( s && predicate ( a ) )
        s._stream<<a;
    return   std::move ( s ) ;
}


}
