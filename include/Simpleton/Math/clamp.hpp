//
//  clamp.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 12/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_clamp_hpp
#define engine_math_clamp_hpp

namespace Math {
  template <typename T>
  constexpr T min(const T a, const T b) {
    return a < b ? a : b;
  }
  
  template <typename T>
  constexpr T max(const T a, const T b) {
    return a > b ? a : b;
  }
  
  template <typename T>
  constexpr T clamp(const T value, const T low, const T high) {
    return value < low ? low : (value > high ? high : value);
  }
  
  template <typename T>
  constexpr T clampMin(const T value, const T low) {
    return value < low ? low : value;
  }
  
  template <typename T>
  constexpr T clampMax(const T value, const T high) {
    return value > high ? high : value;
  }
  
  template <typename T>
  constexpr T clampMag(const T value, const T magnitude) {
    return clamp(value, -magnitude, magnitude);
  }
  
  template <typename T>
  constexpr bool withinRangeInc(const T value, const T low, const T high) {
    return low <= value && value <= high;
  }
  
  template <typename T>
  constexpr bool withinRangeExc(const T value, const T low, const T high) {
    return low < value && value < high;
  }
}

#endif
