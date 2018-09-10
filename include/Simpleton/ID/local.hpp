//
//  local.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_id_local_hpp
#define engine_id_local_hpp

#include <limits>
#include <cassert>

namespace ID {
  ///Creates an ID unique to the instance
  template <typename Int>
  class Local {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    Local() = default;
    ~Local() = default;
  
    ///Make an ID. Only returns positive values. (Even if Int is signed)
    Int make() {
      #ifdef DEBUG
      assert(!prevIsMax && "Too many IDs were made. Int is not large enough");
      if (static_cast<Int>(prev + 1) == std::numeric_limits<Int>::max()) {
        prevIsMax = true;
      }
      #endif
      return ++prev;
    }
    
    ///The next ID will be after the specified ID. next ID = spec ID + 1
    void nextIsAfter(const Int id) {
      #ifdef DEBUG
      if (id == std::numeric_limits<Int>::max()) {
        prevIsMax = true;
      } else {
        prevIsMax = false;
      }
      #endif
      prev = id;
    }
    
    void reset() {
      prev = -1;
      #ifdef DEBUG
      prevIsMax = false;
      #endif
    }
    
  private:
    Int prev = -1;
    #ifdef DEBUG
    bool prevIsMax = false;
    #endif
  };
};

#endif
