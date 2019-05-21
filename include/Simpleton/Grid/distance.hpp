//
//  distance.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_distance_hpp
#define engine_grid_distance_hpp

#include <cmath>
#include "pos.hpp"
#include <algorithm>

namespace Grid {
  /// Euclidian distance squared
  template <typename Float = float>
  Float euclid2(const Pos a, const Pos b) {
    const Float dx = static_cast<Float>(a.x - b.x);
    const Float dy = static_cast<Float>(a.y - b.y);
    return dx*dx + dy*dy;
  }

  /// Euclidian distance
  template <typename Float = float>
  Float euclid(const Pos a, const Pos b) {
    return std::sqrt(euclid2<Float>(a, b));
  }
  
  /// Horizontal distance
  inline Coord horiDist(const Pos a, const Pos b) {
    return std::abs(a.x - b.x);
  }
  
  /// Vertical distance
  inline Coord vertDist(const Pos a, const Pos b) {
    return std::abs(a.y - b.y);
  }
  
  /// The sum of the horizontal distance and the vertical distance
  /// (manhattan distance)
  inline Coord sumAxis(const Pos a, const Pos b) {
    return horiDist(a, b) + vertDist(a, b);
  }
  
  /// The max of the horizontal distance and the vertical distance
  /// (chebyshev distance)
  inline Coord maxAxis(const Pos a, const Pos b) {
    return std::max(horiDist(a, b), vertDist(a, b));
  }
}

#endif
