#pragma once

namespace stepworks{
    
    //
    
    template <typename Ta, template<typename...> typename Form>
    struct auto_removing_instance{
        Ta&  _entry;
        Form<Ta>& _owner;
        operator Ta&() { return  _entry;}
        auto_removing_instance(Ta& a, Form<Ta> & ma):_entry(a), _owner(ma){           
        }
        ~auto_removing_instance(){
            _owner.remove_object(_entry);
        }
        
    };
    
    
    template <typename Ta, typename Tb, template<typename...> typename Form>
    struct auto_removing_instance_x{
        Ta&  _entry;
        Tb   _extra;
        Form<Ta>& _owner;
        operator Ta&() { return  _entry;}
        auto_removing_instance_x(Ta& a, Form<Ta> & ma, Tb x):_entry(a), _owner(ma), _extra(x){           
        }
        ~auto_removing_instance_x(){
            _owner.remove_object(_entry.hash_code(), _extra);
        }
    };
    
    
    
}
