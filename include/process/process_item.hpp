#pragma once

///Neuimplementierung

#include "continuation_stack.hpp"

namespace stepworks::process {

//Base should be a pair <po,processing>

template <typename ...>
struct process_item;

template <typename Base, typename ...Rest>
struct process_item<Base,Rest...>: process_item<Rest...>    //Base-> po
{
  // using rest_t  = decltype ( std::declval< Rest...>);
  // using total_t =  std::tuple<Base,Rest... > ;

    using continuation_t =  stepworks::process::continuation_item< Base, Rest...> ;
   
    Base _base = Base{};
    process_item(Base && b,
                               Rest&&... r):
        process_item<Rest...>
        (           std::move(r)...        ) 
        , _base(std::move(b))
        {}

    process_item(Base && b,
                               process_item<Rest...>&& r):
        process_item<Rest...>        ( std::move(r)     ) 
        , _base(std::move(b))
        {}
        
        
    constexpr unsigned int elm_count()const {
        return 1+ next(*this);
    }
    //constexpr  
    auto return_item()const -> decltype(  next(*this).return_item()  ){
        return (*this)._return_item();
    }
    
    const process_item<Rest...>&  inner()const{
        return *this;
    }
    
};

template <typename Base>
struct process_item<Base>
{
    constexpr unsigned int elm_count()const {
        return 1;
    }
    
    Base _base;
    process_item(Base&& b):
        _base(std::move(b))
        {}
    /*    
    process_item<Base>():
        _base{Base{}}{}    */
    constexpr  auto return_item()const -> const process_item<Base>&{
        return (*this)._return_item();
    }        
};


template <typename H, typename ...R>
    //constexpr 
    const process_item< R...>&   next( const   process_item<H, R...>& here){
        return (const process_item< R...>&) here;
    }
    
    
    template <typename Foab>
    auto make_item(Foab&& foab){
        return process_item< decltype(  foab  )> ( std::move(foab));
    }
    
    /*
     process_item< 
        decltype(  stepworks::make_foab<int,int>( stepworks::ident<int> ) )
    > 
        item_ident(stepworks::make_foab<int,int>( stepworks::ident<int>));
     */
    
    
}
