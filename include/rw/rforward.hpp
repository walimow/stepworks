#pragma once

#include <foab.first/isvalid.hpp>
#include <xtypes.hpp>
#include <core/optional_type.hpp>

using stepworks::types::var_t;

namespace stepworks {

//  template <typename ...>   struct fw;


template <typename Ta,
          template <typename... > typename Src,
          template <typename > typename Form
          >
struct fw //<Ta, Src<Ta>, Form<Ta>>
{
    using atype=Ta;
    //const
    Src<Ta> _src;
    typename Src<Ta>::iterator _it;
    Ta _get()const {
        return *_it;
    }

    fw()=default;
    fw(const fw&)=default;
    fw(Src<Ta>&&s)
        :_src(s) {
        _it = _src.begin();
    }

    bool test;

    fw(Src<Ta>&&s, const typename Src<Ta>::iterator& it)
        :_src(s), _it(it) {
        test= _it==s.end();
        test= _it==_src.end();
    }


    std::pair<Ta,  typename Src<Ta>::const_iterator> _get_inc()const {
        return  std::make_pair(  *_it, ++_it);
    }

    operator bool()const {
        return ( _it != _src.end()  );
    }

    Form<Ta> operator *()const {
        (*this) ?  *_it : Form<Ta> {};
    }

};

/*
template<typename Ta,
    template <typename... > typename Src,
    template <typename > typename Form
    >
auto  _go_ ( fw<Ta, Src, Form >&& src)->std::pair<Form<Ta>,  fw<Ta, Src,Form> >
    {
       // fw<Ta, Src, Form >s =std::move(src);
        if (std::move( src )  )
        {
            return std::make_pair(
                    std::move(src)._get()
                    ,
                    fw<Ta, Src, Form > {
                        std::move(src)._src,
                       std::move( src)._it
                    }
            );
        }
        else
            return std::make_pair( Form<Ta>{} , std::move( src));
    }

template <typename Ta, template <typename... > typename Src, template <typename > typename Form=var_t  >
auto make_forward_readeable( Src<Ta>&& s)-> fw <Ta, Src, Form>{
 fw <Ta, Src, Form>  r = fw <Ta, Src, Form>{ std::move(s), r._src.begin() };
  //  r._it=r._src.begin();
    return std::move(r);
}*/


template <typename Ta, template <typename... > typename Src, template <typename > typename Form=var_t  >
auto make_forward_readeable( Src<Ta>&& s)-> fw <Ta, Src, Form> {
    fw <Ta, Src, Form>  r = fw <Ta, Src, Form> { std::move(s) };

    r._it=r._src.begin();
    auto test=r._it==r._src.end();
    return r; //!
}

template <typename Ta, template <typename... > typename Src, template <typename > typename Form=var_t  >
auto make_forward_readeable( Src<Ta> &&s, const typename Src<Ta>::iterator& it )-> fw <Ta, Src, Form> {
    return std::move(  fw <Ta, Src, Form> { std::move(s), it });
}


template<typename Ta,
         template <typename... > typename Src,
         template <typename > typename Form
         >
auto  _go_ ( fw<Ta, Src, Form >&& src  )->std::pair<Form<Ta>,  fw<Ta, Src,Form> >
{
    if ( src )
    {
        auto test0 = src._it ==src._src.end();
        auto a0  = src._get();
        ++src._it;
        return std::make_pair(
                   a0,
                   make_forward_readeable( std::move(src._src), src._it)
               );
    }
    else
        return std::make_pair( Form<Ta> {}, src);
}


/*
template<typename Ta,
         template <typename... > typename Src,
         template <typename > typename Form
         >
auto  _go_ ( fw<Ta, Src, Form >&& src , bool (*predicate)(const Ta&) )->std::pair<Form<Ta>,  fw<Ta, Src,Form> >
{
    if ( src )
    {
        auto a0  = src._get();
        auto it1 =  ++src._it;
        return std::make_pair(
                    a0,
                   make_forward_readeable( std::move(src._src), src._it)
                    );
    }
    else
        return std::make_pair( Form<Ta> {}, src);
}
*/

}
