//
//  pos.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 8/5/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#ifndef UTIL_POS_HPP
#define UTIL_POS_HPP

#include <cmath>

struct Pos {
  int x, y;
};

constexpr Pos operator+(const Pos lhs, const Pos rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

constexpr Pos &operator+=(Pos &lhs, const Pos rhs) {
  return lhs = lhs + rhs;
}

constexpr Pos operator-(const Pos lhs, const Pos rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

constexpr Pos operator*(const Pos lhs, const int rhs) {
  return {lhs.x * rhs, lhs.y * rhs};
}

constexpr bool operator==(const Pos lhs, const Pos rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr bool operator!=(const Pos lhs, const Pos rhs) {
  return !(lhs == rhs);
}

inline int distance2(const Pos a, const Pos b) {
  const int dx = a.x - b.x;
  const int dy = a.y - b.y;
  return dx * dx + dy * dy;
}

inline float distance(const Pos a, const Pos b) {
  return static_cast<float>(std::sqrt(distance2(a, b)));
}

#endif
