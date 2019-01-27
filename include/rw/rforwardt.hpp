
#pragma once

#include <foab.first/isvalid.hpp>
#include <xtypes.hpp>
#include <util/optional_type.hpp>

using stepworks::types::var_t;

namespace stepworks {

//  template <typename ...>   struct fw_t;


template <typename Ta,
          template <typename... > typename Src,
          template <typename > typename Form
          >
struct fw_t //<Ta, Src<Ta>, Form<Ta>>
{
    using atype=Ta;
    //const
    Src<Ta>&& _src;
    typename Src<Ta>::iterator _it;
    Ta _get()const {
        return *_it;
    }

    fw_t()=default;

    fw_t(Src<Ta>&&s)
        :_src(std::move(s)) {
        _it = _src.begin();
    }

//    bool test;
    fw_t(Src<Ta>&&s, const typename Src<Ta>::iterator& it)
        :_src(std::move(s)), _it(it) {
  //      test= _it==_src.end();
    }


    std::pair<Ta,  typename Src<Ta>::const_iterator> _get_inc()const {
        return  std::make_pair(  *_it, ++_it);
    }

    operator bool()const {
        return ( _it != std::move( _src).end()  );
    }

    Form<Ta> operator *()const {
        (*this) ?  *_it : Form<Ta> {};
    }

};



template <typename Ta, template <typename... > typename Src, template <typename > typename Form=var_t  >
auto make_forward_readeable_t( Src<Ta>&& s)-> fw_t <Ta, Src, Form> {
    fw_t <Ta, Src, Form>  r = fw_t <Ta, Src, Form> { std::move(s) };

    r._it=r._src.begin();
    auto test=r._it==r._src.end();
    return std::move(r);
}

template <typename Ta, template <typename... > typename Src, template <typename > typename Form=var_t  >
auto make_forward_readeable_t( Src<Ta> &&s, const typename Src<Ta>::iterator& it )-> fw_t <Ta, Src, Form> {
    return std::move(  fw_t <Ta, Src, Form> { std::move(s), it });
}



template<typename Ta,
         template <typename... > typename Src,
         template <typename > typename Form
         >
auto  _go_ ( fw_t<Ta, Src, Form >&& src  )->std::pair<Form<Ta>,  fw_t<Ta, Src,Form> >
{
    if ( src )
    {
        //    auto test0 = src._it ==src._src.end();
        auto a0  = src._get();
        auto it1 =  ++src._it;
        //   auto test = src._it ==src._src.end();
        return std::make_pair(
                   a0,
                   make_forward_readeable_t( std::move(std::move(src._src)), src._it)
               );
    }
    else
        return std::make_pair( Form<Ta> {}, std::move(src));
}

}
