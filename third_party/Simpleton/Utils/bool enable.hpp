//
//  bool enable.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_bool_enable_hpp
#define engine_utils_bool_enable_hpp

namespace Utils {
  template <typename T>
  T boolEnable(const bool status, T value) {
    return status ? value : T{};
  }
}

#endif
