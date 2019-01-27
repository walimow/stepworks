#pragma  once

#include <optional>
#include <string>
#include <sstream>

namespace stepworks::process {

struct unset {};


template <typename ...>   struct continuation_item;

template <typename Ta>
using continuation_entry=std::optional< Ta>;



template <typename Ta>
auto continuation_entry_optional( const continuation_entry<Ta>& e, const Ta&  _default)->const Ta& {   
    
    return (e) ? *e : _default;        
};


template <typename Ta>
auto continuation_entry_text( const continuation_entry<Ta>& e, const std::string& sdefault="unset")->std::string {   
    
    if  (e) {
            std::ostringstream ost; 
            ost<<typeid(*e).name()<<":\t"<< *e<<'\t'; 
            return ost.str();
    }
    else
        return sdefault;
};


template <typename Ta>
struct continuation_item<Ta> {
    continuation_entry<Ta> _entry;
    constexpr unsigned int pos()const {
        return 0;
    }
};

template <typename Ta, typename ...Rest>
struct continuation_item<Ta, Rest...>:  continuation_item< Rest...>
{
    continuation_entry<Ta> _entry;


//            template <int N>
//            auto get()-> decltype(  ){}

    constexpr unsigned int pos()const {
        return 1+next(*this).pos();
    }
};


template <typename H, typename ...R>
constexpr const continuation_item< R...>&   next( const   continuation_item<H, R...>& here) {
    return (continuation_item< R...>&) here;
}


//        template <int N, typename ...>        auto sel();
template <std::size_t N, typename Ta, typename ...Rest>
struct _g {
    static auto _sel_(const continuation_item<Ta,Rest...>& a)//->decltype(sel<N-1,Rest...>)
    {
        return _g<N-1,Rest...>::_sel_ ( next(a)  );
    }
};


template <  typename Ta, typename ...Rest>
struct  _g<0,Ta,Rest...>
{
    static  auto _sel_(const continuation_item<Ta,Rest...>& a)-> continuation_entry<Ta> {
        return  a._entry ;
    }
};


template <std::size_t N, typename Ta, typename ...Rest>
auto sel( const continuation_item<Ta,Rest...>& a ) {
    return  _g<N,Ta,Rest...>::_sel_(a);
}



}
