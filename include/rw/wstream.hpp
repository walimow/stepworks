#pragma once


#include <foab.first/isvalid.hpp>
#include <xtypes.hpp>
#include <util/optional_type.hpp>
#include <util/optional.hpp>

#include <foab_fab.hpp>
#include <fab.hpp>

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
        //Stream&&  _dest;
        using _argument_type=Ta;
        wstream operator () ( const Ta& a, wstream && dest ) const
        {
            std::move ( dest )._stream<<a;
            return wstream {std::move ( dest ) };
        }
    };

    Stream&& _stream;
    std::string _post;

    operator bool() const
    {
        return ! _stream.eof() && _stream.good();    //?
    }

    wfoab write()
    {
        return wfoab {} ;
    }

};





template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form = var_t
         >
auto  _go_ ( wstream<Ta, Src,Form >&& src, const Form<Ta>& a0 )->wstream<Ta,Src,Form> {

    wstream<Ta, Src > s =std::move ( src );
 
    if ( s )
    {
        using W =  wstream<Ta, Src, Form >;
        return  stepworks::apply_optional
        //  < Ta,W,Form >
        ( a0,
        std::move ( s ),
        [] ( const Ta& a,W&& w_ )->W { auto w=std::move ( w_ ); w<<a; return std::move ( w );} );
    }
    return   std::move ( s ) ;
}


template<typename Ta,
         typename  Src = std:: istream,
         template <typename > typename Form = var_t
         >
auto  _go_ ( wstream<Ta, Src,Form >&& src, const Form<Ta>& a0, bool (*predicate)(const Ta&) )->wstream<Ta,Src,Form> {

    wstream<Ta, Src > s =std::move ( src );
 
    if ( s )
    {
        using W =  wstream<Ta, Src, Form >;
        return  stepworks::apply_optional
        //  < Ta,W,Form >
        ( a0,
        std::move ( s ),
        [] ( const Ta& a,W&& w_ )->W { auto w=std::move ( w_ ); w<<a; return std::move ( w );}
        , predicate );
    }
    return   std::move ( s ) ;
}

template<typename Ta,
         typename  Src = std:: istream
         >
auto  _go_ ( wstream<Ta, Src, var_t >&& src, const var_t<Ta>& a0 )->wstream<Ta,Src,var_t> {

    //   static_assert(std::is_same<var_t <int>,  std::optional<int>>::value,"valt_t!");

    
    wstream<Ta, Src,var_t > s =std::move ( src );
    if ( s )
    {
        using W =  wstream<Ta, Src, var_t >;
        return  stepworks::apply_optional
        //  < Ta,W,var_t >
        ( a0,
        std::move ( s ),
        [] ( const Ta& a,W&& w_ )->W { auto& w=std::forward<W&> ( w_ );
            w._stream<<a; 
            if (w._post.size())
                w._stream << w._post;
      //      std::cout<<"? "<<a<<"\t!";
           
            return std::move ( w );} );
    }
    return   std::move ( s ) ;
}


template<typename Ta,
         typename  Src = std:: istream
         >
auto  _go_ ( wstream<Ta, Src, var_t >&& src, const var_t<Ta>& a0 , bool (*predicate)(const Ta&))->wstream<Ta,Src,var_t> {

    //   static_assert(std::is_same<var_t <int>,  std::optional<int>>::value,"valt_t!");

    
    wstream<Ta, Src,var_t > s =std::move ( src );
    if ( s  )
    {
        using W =  wstream<Ta, Src, var_t >;
        return  stepworks::apply_optional
        //  < Ta,W,var_t >
        ( a0,
        std::move ( s ),
        [] ( const Ta& a,W&& w_ )->W { auto& w=std::forward<W&> ( w_ );
            w._stream<<a; 
            if (w._post.size())
                w._stream << w._post;
      //      std::cout<<"? "<<a<<"\t!";
           
            return std::move ( w );},
        predicate
        );
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
auto  _go_ ( wstream<Ta, Src, Form  >&& src, Ta&& a, bool(*predicate)(const Ta&) )
{
    wstream<Ta, Src, Form > s =std::move ( src );
    if ( s && predicate(a))
        s._stream<<a;
    return   std::move ( s ) ;
}


}
