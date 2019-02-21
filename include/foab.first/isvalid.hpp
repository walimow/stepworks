#pragma once

namespace stepworks::first{
    
    
template <typename Ta>
struct is_valid{
  //  bool operator ( )(const Ta&)const {         return true;    }
  //  bool operator ( )()const {         return false;    }
    
  constexpr  bool f1( const Ta&) const {         return true;    }

  constexpr  bool f0()const {         return false;    }

  //
  //constexpr  bool ft0()const {         return false;    }
};

    
}
