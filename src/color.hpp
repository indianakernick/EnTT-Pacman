//
//  color.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <cassert>

using ColIdx = uint8_t;

enum class Color : ColIdx {
  black,
  red,
  green,
  yellow,
  blue,
  magenta,
  cyan,
  white
};

inline ColIdx color_sys(const Color c) {
  assert(static_cast<ColIdx>(c) < 8);
  return static_cast<ColIdx>(c);
}

inline ColIdx color_bri(const Color c) {
  assert(static_cast<ColIdx>(c) < 8);
  return 8 + static_cast<ColIdx>(c);
}

inline ColIdx color_rgb(const ColIdx r, const ColIdx g, const ColIdx b) {
  assert(r < 6);
  assert(g < 6);
  assert(b < 6);
  return 16 + 36 * r + 6 * g + b;
}

inline ColIdx color_grey(const ColIdx y) {
  assert(y < 24);
  return 232 + y;
}

#endif