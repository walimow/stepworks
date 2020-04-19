
#pragma once

///Forward-Reader with Base&&   (because std::list in libstdc++)

#include <foab.first/isvalid.hpp>
#include <core/optional_type.hpp>

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

    fw_t(Src<Ta>&&s, const typename Src<Ta>::iterator& it)
        :_src(std::move(s)), _it(it) {
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

    ///position support
    using position_t = typename Src<Ta>::iterator;
  
};


template <typename Ta,
          template <typename... > typename Src,
          template <typename > typename Form
          >
auto  get_position  (const fw_t<Ta, Src, Form>& fw)
{
    return fw._it;
}

template <typename Ta,
          template <typename... > typename Src,
          template <typename > typename Form
          >
void set_position  ( fw_t<Ta, Src, Form>& fw_, typename fw<Ta, Src, Form>::position_t&& pos)
{
    fw_._it = std::move(pos);
}



template <typename Ta, template <typename... > typename Src, template <typename > typename Form=var_t  >
auto make_forward_readeable_t( Src<Ta>&& s)-> fw_t <Ta, Src, Form> {
    fw_t <Ta, Src, Form>  r = fw_t <Ta, Src, Form> { std::move(s) };

    r._it=r._src.begin();
    return r;
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
        auto a0  = src._get();
        ++src._it;
        return std::make_pair(
                   a0,
                   make_forward_readeable_t( std::move(std::move(src._src)), src._it)
               );
    }
    else
        return std::make_pair( Form<Ta> {}, std::move(src));
}





    
}
