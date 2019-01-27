#pragma once

#include <xtypes.hpp>

namespace stepworks{
    
    template<typename Ta,
        template <typename> typename Form  = stepworks::types::var_t >
    using xT= Form<Ta>;

    
    template<typename Ta>
    using xTi=   stepworks::types::var_t_info<Ta>;
    
    
    template<typename Ta, typename Tx=Ta>
    using xTt=   stepworks::types::var_t_type<Tx,Ta>;
    
}
