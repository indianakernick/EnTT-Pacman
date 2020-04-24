//
//  scale.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_scale_hpp
#define engine_math_scale_hpp

#include <limits>
#include <cstdint>
#include <type_traits>
#include "../Utils/bits.hpp"

namespace Math {
  ///Scales a value from one range to another
  template <typename T>
  T scale(const T value, const T fromMin, const T fromMax, const T toMin, const T toMax) {
    return (value / (fromMax - fromMin) - fromMin) * (toMax - toMin) + toMin;
  }
  ///Scales a value from its range to a range of 0-1
  template <typename T>
  T fromRange(const T value, const T min, const T max) {
    return (value - min) / (max - min);
  }
  ///Scales a value from a range of 0-1 to a new range
  template <typename T>
  T toRange(const T value, const T min, const T max) {
    return value * (max - min) + min;
  }
  ///Determines the sign of a number and returns -1, 0 or 1
  template <typename T>
  T sign(const T num) {
    if constexpr (std::is_signed<T>::value) {
      return (T(0) < num) - (num < T(0));
    } else {
      return T(0) < num;
    }
  }
  ///Determines the absolute value of a number.
  template <typename T>
  T abs(const T num) {
    if constexpr (std::is_unsigned<T>::value) {
      return num;
    } else if constexpr (std::is_integral<T>::value && std::is_signed<T>::value) {
      const T s = num >> (Utils::bits<T> - 1);
      return (num ^ s) - s;
    } else if constexpr (std::numeric_limits<T>::is_iec559) {
      //@TODO fix for long double
      union {
        uint8_t b[sizeof(T)];
        T f;
      };
      f = num;
      //assumes little endian
      b[sizeof(T) - 1] &= 0x7F;
      return f;
    } else {
      return num < T(0) ? -num : num;
    }
  }
}

#endif
