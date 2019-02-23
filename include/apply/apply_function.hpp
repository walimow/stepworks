#pragma once

#include <util/optional_type.hpp>

#include <type_traits>
//#include  <utility>

using stepworks::types::var_t;


namespace stepworks::application {


template <typename...> struct apply;

template <typename R, typename A>
struct apply<R(const A)> {
    using F = R(*)(const A&);
    F _f;
    constexpr auto operator()(const A&a)const {
        assert(_f);
        return _f(a);
    }
};

template <typename R, typename A>
auto _( R(*f)(const A&)  ) {
    return apply<R(const A&)> {f};
}

///optional/default

template <typename R, typename A>
struct apply<R ( const var_t<A>&),R> {
    using F = R(*)(const A&);
    F _f;
    const R _default;
    constexpr auto operator()(const var_t<A> &a)const {
        assert(_f);
        if (a)
            return _f(*a);
        else
            return _default;
    }

};

template <typename R, typename A>
auto _( R(*f)(const A&), const R& df )
{
    return apply< R(const var_t<A>&),R > {f,df};
}

//optional /handled


template <typename R, typename A>
struct apply<R ( const var_t<A>&), R()> {
    using F = R(*)(const A&);
    F _f;
    R(*_default)() ;
    constexpr auto operator()(const var_t<A> &a)const {
        assert(_f);
        if (a)
            return _f(*a);
        else
            return _default();
    }

    template  < typename Else, template <typename,typename> typename Form>
    constexpr auto operator()(const Form<Else,A>& a0)const {
        struct vis {
            const apply& _here;
            auto operator()(const A&a)const {
                return _here(a);
            }
            auto operator()(const Else&a)const {

                return _here._default();
            }
        };
        return std::visit(vis {*this}, a0);
    }
};


template <typename R, typename A>
auto _( R(*f)(const A&),  R(*df)() )
{
    return apply< R(const var_t<A>&), R() > {f,df};
}




template <typename R, typename A, typename Else>
struct apply<R ( const var_t<A>&), R(const Else&)> {
    using F = R(*)(const A&);
    F _f;
    R(*_else)(const Else&) ;

      template  < template <typename...> typename Form>      ///clang-problem
  //  template  < template <typename,typename> typename Form>
    constexpr auto operator()(const Form<Else,A>& a0)const {
        struct vis {
            const apply& _here;
            auto operator()(const A&a)const {
                return _here._f(a);
            }
            auto operator()(const Else&a)const {

                return  _here._else(a);
            }
        };
        return std::visit(vis {*this}, a0);
    };
};

template <typename R, typename A, typename Else>
auto _( R(*f)(const A&),  R(*df)( const Else&) )
{
    return apply< R(const var_t<A>&), R(const Else&) > {f,df};
}


///?here?
/*
template <typename Ta, template<typename...> R, typename Tb=ta>
struct apply<> 
*/

}
