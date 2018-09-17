//
//  depth.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_depth_hpp
#define engine_graphics_2d_depth_hpp

namespace G2D {
  /// Get the depth of a depth enum
  template <typename Enum>
  constexpr float depth(Enum);
  constexpr float depth(float);
  constexpr float depth(double);
  constexpr float depth(long double);
}

#include "depth.inl"

#endif
