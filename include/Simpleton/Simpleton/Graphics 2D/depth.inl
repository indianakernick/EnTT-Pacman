//
//  depth.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

namespace G2D::detail {
  template <typename Enum>
  constexpr auto depth(const Enum e, int) -> decltype(Enum::COUNT, float{}) {
    return static_cast<float>(e) / static_cast<float>(Enum::COUNT);
  }
  
  template <typename Enum>
  constexpr float depth(const Enum e, long) {
    return static_cast<float>(e) / 255.0f;
  }
}

template <typename Enum>
constexpr float G2D::depth(const Enum e) {
  return detail::depth(e, 0);
}

constexpr float G2D::depth(const float d) {
  return d;
}

constexpr float G2D::depth(const double d) {
  return d;
}

constexpr float G2D::depth(const long double d) {
  return d;
}
