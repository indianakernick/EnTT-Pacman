//
//  global.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_id_global_hpp
#define engine_id_global_hpp

#include <limits>
#include <cassert>

namespace ID {
  ///Creates a globally unique ID. Group is a type the identifies this global group
  template <typename Int, typename Group>
  class Global {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    Global() = delete;
    ~Global() = delete;
  
    ///Make an ID. Only returns positive values. (Even if Int is signed)
    static Int make() {
      #ifdef DEBUG
      assert(!prevIsMax && "Too many IDs were made. Int is not large enough");
      if (static_cast<Int>(prev + 1) == std::numeric_limits<Int>::max()) {
        prevIsMax = true;
      }
      #endif
      return ++prev;
    }
    
    ///The next ID will be after the specified ID. next ID = spec ID + 1
    static void nextIsAfter(const Int id) {
      #ifdef DEBUG
      if (id == std::numeric_limits<Int>::max()) {
        prevIsMax = true;
      } else {
        prevIsMax = false;
      }
      #endif
      prev = id;
    }
 
  private:
    static Int prev;
    #ifdef DEBUG
    static bool prevIsMax;
    #endif
  };
  
  template <typename Int, typename Group>
  Int Global<Int, Group>::prev = -1;
  
  #ifdef DEBUG
  template <typename Int, typename Group>
  bool Global<Int, Group>::prevIsMax = false;
  #endif
}

#endif
