#pragma once

#include <apply.hpp>

namespace  stepworks{
    
    template <typename...>  
    struct step;
  /*  
    template <typename Ta, typename R>
    class step_abstract{
    public:    
        virtual ~step_abstract(){}
       
       
       virtual R operator()(const Ta&)=0;
        
    };
*/    
    template <typename Ta, typename R>
    struct step<R(const Ta)> //: public step_abstract<Ta,R>
    {
    public:
        stepworks::application::apply<R(const Ta)> _app;
        using F = typename stepworks::application::apply<R(const Ta)>::F;
        
        auto operator()(const Ta& a)const{
            return _app(a);
        }
        
    };
    
}
