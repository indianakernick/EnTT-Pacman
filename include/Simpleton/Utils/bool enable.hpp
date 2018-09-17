//
//  bool enable.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_bool_enable_hpp
#define engine_utils_bool_enable_hpp

#include <type_traits>
#include "int least.hpp"

//these functions are about 90% faster than a naive if statement
//and about 20% faster than a multiply

namespace Utils {
  ///Returns value if status is true and returns 0 if status is false
  template <typename T>
  inline std::enable_if_t<std::is_integral<T>::value, T>
  boolEnable(const bool status, const T value) {
    return -static_cast<T>(status) & value;
  }

  ///Returns value if status is true and returns 0 if status is false
  template <typename T>
  inline std::enable_if_t<std::is_enum<T>::value, T>
  boolEnable(const bool status, const T value) {
    using Int = std::underlying_type_t<T>;
    return static_cast<T>(-static_cast<Int>(status) & static_cast<Int>(value));
  }

  ///Returns value if status is true and returns 0.0 if status is false
  template <typename T>
  inline std::enable_if_t<std::is_floating_point<T>::value, T>
  boolEnable(const bool status, const T value) {
    using Int = uint_fit_t<T>;
    union {
      T f;
      Int i;
    } val;
    val.f = value;
    val.i &= -static_cast<Int>(status);
    return val.f;
  }

  ///Returns value if status is true and returns nullptr if status is false
  template <typename T>
  inline std::enable_if_t<std::is_pointer<T>::value, T>
  boolEnable(const bool status, const T value) {
    union {
      T p;
      uintptr_t i;
    } val;
    val.p = value;
    val.i &= -static_cast<uintptr_t>(status);
    return val.p;
  }
}

#endif
