//
//  vectors.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 4/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_vectors_hpp
#define engine_math_vectors_hpp

#include <cmath>
#include <algorithm>
#include <glm/vec2.hpp>

namespace Math {
  ///Calculate the aspect ratio of a 2D size
  template <typename Return, typename Argument>
  Return aspectRatio(const Argument size) {
    return static_cast<Return>(size.x) / static_cast<Return>(size.y);
  }
  
  ///Calulate the aspect ratio of a 2D size
  template <typename Argument>
  auto aspectRatio(const Argument size) {
    return aspectRatio<decltype(size.x)>(size);
  }
  
  ///Calculate the squared distance between 2D int vectors
  template <typename Vec>
  auto distance2(const Vec a, const Vec b) -> decltype(a.x) {
    using Scalar = decltype(a.x);
    static_assert(
      std::is_integral<Scalar>::value,
      "glm/gtx/norm.hpp provides distance2 for float vectors"
    );
    
    const Scalar x = a.x - b.x;
    const Scalar y = a.y - b.y;
    return x*x + y*y;
  }
  
  ///Get a vector from an angle and a magnitude
  template <typename Return, typename Angle, typename Mag>
  glm::tvec2<Return> angleMag(const Angle angle, const Mag mag) {
    return {
      static_cast<Return>(std::cos(angle) * mag),
      static_cast<Return>(std::sin(angle) * mag)
    };
  }
  
  ///Get a vector from an angle and a magnitude
  template <typename Angle, typename Mag>
  glm::tvec2<Mag> angleMag(const Angle angle, const Mag mag) {
    return angleMag<Mag, Angle, Mag>(angle, mag);
  }
  
  template <typename Angle, typename Vec>
  Angle angle(const Vec vec) {
    return std::atan2(vec.y, vec.x);
  }
  
  template <typename Vec>
  auto angle(const Vec vec) -> decltype(vec.x) {
    return angle<decltype(vec.x), Vec>(vec);
  }
  
  template <typename Vec>
  Vec clampLength(const Vec vec, const decltype(vec.x) maxLength) {
    const auto length = std::sqrt(vec.x*vec.x + vec.y*vec.y);
    return vec / length * std::min(length, maxLength);
  }
  
  template <typename Vec>
  int quadrant(const Vec v) {
    /*
          +y
          │
      1   3   3
          │
    ──1───3───3──  +x
          │
      0   2   2
          │
    
    */
    using Scalar = decltype(v.x);
    const int xPlus = v.x >= Scalar(0);
    const int yPlus = v.y >= Scalar(0);
    return (xPlus << 1) | yPlus;
  }
  
  template <typename VecA, typename VecB>
  bool sameQuadrant(const VecA a, const VecB b) {
    return quadrant(a) == quadrant(b);
  }
}

#endif
