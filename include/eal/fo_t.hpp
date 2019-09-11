#pragma  once

namespace stepworks::eal::fo{
    
///build function objects

template <typename ...> struct ft;    
    
template < typename R, typename ...Args>
struct ft<R,Args...> {
    using F = R(*)(Args...);
    F _f;

    auto operator()(Args&&...args) noexcept {
        return _f(args...);
    }
};

template < typename F>
struct ft<F> 
{
     F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
};


struct factor
{
    template < typename R,  typename ...Args>
    constexpr  static auto gen( R(*f)(Args&&...) ) noexcept {
        return  ft< R,Args...> {f} ;
    }
    
    template < typename F>
    constexpr static  auto gen( F&& f ) noexcept {
        return  ft< F> {std::move(f)} ;
    }
};


    
}
