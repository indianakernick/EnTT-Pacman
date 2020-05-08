//
//  dir.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 8/5/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//

#ifndef UTIL_DIR_HPP
#define UTIL_DIR_HPP

#include <cstdint>
#include "int_range.hpp"

enum class Dir : std::uint8_t {
  up,
  right,
  down,
  left,
  none,

  begin = up,
  end = none
};

constexpr bool isHori(const Dir dir) {
  switch (dir) {
    case Dir::right:
    case Dir::left:
      return true;
    default:
      return false;
  }
}

constexpr Dir opposite(const Dir dir) {
  switch (dir) {
    case Dir::up:    return Dir::down;
    case Dir::right: return Dir::left;
    case Dir::down:  return Dir::up;
    case Dir::left:  return Dir::right;
    case Dir::none:  return Dir::none;
  }
}

constexpr Dir rotateCW(const Dir dir) {
  switch (dir) {
    case Dir::up:    return Dir::right;
    case Dir::right: return Dir::down;
    case Dir::down:  return Dir::left;
    case Dir::left:  return Dir::up;
    case Dir::none:  return Dir::none;
  }
}

constexpr Dir &operator++(Dir &dir) {
  return dir = static_cast<Dir>(static_cast<int>(dir) + 1);
}

constexpr IntRange<Dir> dir_range {Dir::begin, Dir::end};

#endif
