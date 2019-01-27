#pragma once

#include <type_traits>
#include <string>
#include <optional>
#include <variant>
#include <utility>

#include <foab.hpp>

#include <util/argtype.hpp>
#include <util/offtype.hpp>
#include <util/optional_type.hpp>

namespace stepworks {
namespace types {


//Fab::fi(const f1)

template<typename Ta, typename Tb, typename Fab>
auto apply( const var_t_type<Ta> & a0,  const Fab& f)
-> var_t_type<Ta,Tb> {                                             //b or defectious a
    struct vs {
        const Fab& f;
        auto operator() (  const Ta& s)const -> var_t_type<Ta,Tb> {
            using T = arg_1_t< typename PM_traits<decltype(&Fab::f1)>::member_type>;
            return   f.f1(             std::forward<T> (s )   );
        }
        auto operator() ( const off_type<Ta> & s)const -> var_t_type<Ta,Tb> {
            return    std::move(s);
        }
    } ;
    return    std::visit(vs{f},   a0 );
}



template<typename Ta, typename Tb, typename Fab>
auto apply(   const var_t_info<Ta>&   a0, const Fab& f)
->var_t_info<Tb > {

    struct vs {
        const Fab& f;
        auto operator() ( const  Ta& s)const ->var_t_info<Tb> {
            using T = arg_1_t< typename PM_traits<decltype(&Fab::f1)>::member_type>;
            return   f.f1(        std::forward< T >( s )   );
        }
        auto operator() ( const  off_info & s)const->var_t_info<Tb> {
            return     s;
        }
    } ;
    return    std::visit(vs{f},   a0 );
}



////////////


template<typename Ta, typename Tb,  typename Fab>
auto apply(const   var_t< Ta>& a0, const Fab& f)
->var_t<Tb> {

    auto a0_ = std::move(a0);
    if (a0_)
        return f.f1(*a0_);
    else {
        return var_t<Tb> {};    //off_type <Tb>{} ?
    }

}


///todo apply_optional


//the Fab0

///expects  a 'Fab0':
///  a->b (like fab)
/// ()->b  (off as void)

template<typename Ta, typename Tb,  typename Fab0>
auto apply_optional_void(const var_t< Ta>& a0, const Fab0& f)->Tb {
    auto a0_ = std::move(a0);
    if (a0_)
        return f.f1(*a0_);
    else
        return f.f0();
}


template<typename Ta, typename Tb,  typename Fab0>
auto apply_optional_void_r(const var_t< Ta>& a0,  Fab0& f)->Tb {
    auto a0_ = std::move(a0);
    if (a0_)
        return f.f1(*a0_);
    else
        return f.f0();
}

template<typename Ta, typename Tb, typename Fab0>
auto apply_optional_void(const   var_t_info< Ta>& a0, const Fab0& f)->Tb {

    struct vs {
        const Fab0& f;
        auto operator() (  const Ta& s)const {

            using T = typename PM_traits<decltype(&Fab0::f1)>::member_type;
            using R = arg_1_t<  T >;
            return   f.f1( std::forward< R >(  s )      );
        }

        auto operator() ( const off_info & s  )const {
            return    f.f0();
        }
    } ;
    //return    std::visit(vs,   std::move(a0),f );
    return    std::visit(vs{f},   a0);
}

/// (a (a))->b    :optional a, containeing a failtype x(default an a) to b
template<typename Ta, typename Tb, typename Fab0, typename Tx=Ta>
auto apply_optional_void(const  var_t_type<Ta,Tx> & a0, const Fab0& f)->Tb {

    struct vs {
        const Fab0& f;
        auto operator() (  const Ta& s)const {
            using T = arg_1_t< typename PM_traits<decltype(&Fab0::f1)>::member_type>;
//
            //  using T =  typename  PM_traits< decltype (&Fab0::operator()) >::member_type;
            return   f.f1(    std::forward<T>(s)   );
        }
        auto operator() ( const off_type<Tx> & s  )const {
            return    f.f0();
        }

    } ;
    return    std::visit(vs{f},  a0);
}

//***       apply_optional, reduces mentioning types in application of fab

//fab is  an argument  template
template< template<typename> typename Fab,
          template<typename ...> typename Frame,
          typename Ta,
          typename Off>
auto apply_fab(
    const Fab<Ta>& fab,
    const Frame<Off,Ta> & a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab<Ta>::f1)>::member_type>;
    return  stepworks::types::apply_optional_void< Ta,Tb  >(a,fab);
}

//fab is  an  template, where argument and return type are generic
template< template<typename, typename> typename Fab,
          template<typename ...> typename Frame,
          typename Ta,
          typename Tb,
          typename Off>
auto apply_fab(
    const Fab<Ta,Tb>& fab,
    const Frame<Off,Ta> & a)
{
    return  stepworks::types::apply_optional_void< Ta,Tb  >(a,fab);
}

//fab is not a template
template< typename Fab,
          template<typename...> typename Frame,
          typename Ta,
          typename Off>
auto apply_fab(
    const Fab& fab,
    const Frame<Off,Ta> & a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab::f1)>::member_type>;
    return  stepworks::types::apply_optional_void< Ta,Tb  >(a,fab);
}




////////////    apply_optional_type : Fabx  contains handling for Off

template<typename Ta, typename Tb,  typename Fabx>
auto apply_optional_type(const  var_t< Ta>& a0, const Fabx& f)->Tb {
    return apply_optional_void( a0, f);       ///opional   : no type
}

template<typename Ta, typename Tb,  typename Fabx, typename Tx=Ta>
auto apply_optional_type(const  var_t_info<Ta >& a0, const Fabx& f)->Tb {

    struct vs {
        const Fabx& f;
        auto operator() (  const Ta& s)const {
//            using T =  typename  PM_traits< decltype (&Fabx::operator()) >::member_type;
            return   f.f1( /*std::forward< T > >(*/  s         );
        }
        auto operator() ( const off_info & s  )const {
            return    f.ft0 (s);       //maybe type problem (on info_t)
            ///ft0 : off_t_type-handler
        }
    } ;
    return    std::visit(vs{f },   a0 );
}


template<typename Ta, typename Tb, typename Fab0t, typename Tx=Ta>
auto apply_optional_type(const  var_t_type<Ta,Tx> & a0, const Fab0t& f)->Tb {

    struct vs {
        const Fab0t& f;
        auto operator() (  const Ta& s)const {
            //  using T =  typename  PM_traits< decltype (&Fab0::operator()) >::member_type;
            return   f.f1(  s   );
        }
        auto operator() ( const off_type<Tx> & s )const {
            return    f.ft0( s);
        }
    } ;
    return    std::visit(vs{f},  a0);
}

}
}

//***       apply_optional, reduces mentioning types in application of fab

//fab is  an argument  template
template< template<typename> typename Fab,
          template<typename...> typename Frame,
          typename Ta,
          typename Off>
auto apply_fabt(
    const Fab<Ta>& fab,
    const Frame<Off,Ta> & a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab<Ta>::f1)>::member_type>;
    return  stepworks::types::apply_optional_type< Ta,Tb  >(a,fab);
}

//fab is  an  template, which argument and return types are generic
template< template<typename, typename> typename Fab,
          template<typename...> typename Frame,
          typename Ta,
          typename Tb,
          typename Off>
auto apply_fabt(
    const Fab<Ta,Tb>& fab,
    const Frame<Off,Ta> & a)
{
    return  stepworks::types::apply_optional_type< Ta,Tb  >(a,fab);
}

//fab is not a template
template< typename Fab,
          template<typename...> typename Frame,
          typename Ta,
          typename Off>
auto apply_fabt(
    const Fab& fab,
    const Frame<Off,Ta> & a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab::f1)>::member_type>;
    return  stepworks::types::apply_optional_type< Ta,Tb  >(a,fab);
}

////////////////////////////////////////////////////////////////

//***       apply_optional, reduces mentioning types in application of fab


//fab is  an argument  template
template< template<typename> typename Fab,
          template<typename, typename> typename Frame,
          typename Ta,
          typename Off>
auto apply_fab0(
    const Fab<Ta>& fab,
    const Frame<Off,Ta> & a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab<Ta>::f1)>::member_type>;
    return  stepworks::types::apply< Ta,Tb  >(a,fab);
}

//fab is  an  template, which argument and return types are generic
template< template<typename, typename> typename Fab,
          template<typename, typename> typename Frame,
          typename Ta,
          typename Tb,
          typename Off>
auto apply_fab0(
    const Fab<Ta,Tb>& fab,
    const Frame<Off,Ta> & a)
{
    return  stepworks::types::apply< Ta,Tb  >(a,fab);
}


//fab is not a template
template< typename Fab,
          template<typename, typename> typename Frame,
          typename Ta,
          typename Off>
auto apply_fab0(
    const Fab& fab,
    const Frame<Off,Ta> & a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab::f1)>::member_type>;
    return  stepworks::types::apply< Ta,Tb  >(a,fab);
}

//using stepworks::types::var_t;

//spezailisation for optional

template< typename Fab,
          //  template<typename, typename> typename Frame,
          typename Ta>
auto apply_fab0(
    const Fab& fab,
    const typename stepworks::types::var_t<Ta>& a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab::f1)>::member_type>;
    return  stepworks::types::apply_optional_void< Ta,Tb  >(a,fab);
}


template< typename Fab,
          //  template<typename, typename> typename Frame,
          typename Ta>
auto apply_fab(
    const Fab& fab,
    const typename stepworks::types::var_t<Ta>& a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab::f1)>::member_type>;
    return  stepworks::types::apply< Ta,Tb  >(a,fab);
}


template< typename Fab,
          //  template<typename, typename> typename Frame,
          typename Ta>
auto apply_fabt(
    const Fab& fab,
    const typename stepworks::types::var_t<Ta>& a)
{
    using Tb = ret_t < typename PM_traits<decltype(&Fab::f1)>::member_type>;
    return  stepworks::types::apply_optional_type< Ta,Tb  >(a,fab);
}

/// writer 

namespace stepworks{
 
    template <typename Ta,   typename Tb>
    using fwrite_ab=Tb(*)( const Ta&, Tb&& );
    
    template <typename Ta,   typename Tb>
    auto apply_optional(const types::var_t<Ta>& a0, Tb&& b, fwrite_ab<Ta,Tb> f){
        return (a0) ? f( *a0, std::move(b)) : std::move(b);
    }
    
    template <typename Ta,   typename Tb, typename F>
    auto apply_optional(const types::var_t<Ta>& a0, Tb&& b, F f){
        return (a0) ? f( (const Ta&) *a0, std::move(b)) : std::move(b);
    }
    
    
    
    template <typename Ta,   typename Tb>
    auto apply_optional(const Ta& a, Tb&& b, fwrite_ab<Ta,Tb> f){
        return f( a, std::move(b));
    }
    
    ////
    template <typename Ta,   typename Tb, template<typename> typename Form>
    auto apply_optional(const Form<Ta>& a0, Tb&& b, fwrite_ab<Ta,Tb> f){
        return ( a0.index())?  f( std::get<1>(a0)  , std::move(b)) : std::move(b) ;
    }
    
    /*
    template <typename Ta,   typename Tb, typename F>
    auto apply_optional(const  stepworks::types:: var_t<Ta>& a0, Tb&& b, F f){
        return ( a0)?  f( *a0)  , std::move(b)) : std::move(b) ;
    }
    */
    
    /*
    template <typename Ta,   typename Tb>
    auto apply_optional(const types::var_t<Ta>& a0, Tb&& b, fwrite_ab<Ta,Tb> f){
        return (a0) ? f( *a0, std::move(b)) : std::move(b);
    }
    */
    
}
