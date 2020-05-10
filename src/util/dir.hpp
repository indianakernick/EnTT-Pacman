//
//  dir.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 8/5/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#ifndef UTIL_DIR_HPP
#define UTIL_DIR_HPP

#include <cstdint>

// An orthogonal direction
enum class Dir : std::uint8_t {
  up,
  right,
  down,
  left,
  none,

  begin = up,
  end = none
};

constexpr Dir opposite(const Dir dir) {
  switch (dir) {
    case Dir::up:    return Dir::down;
    case Dir::right: return Dir::left;
    case Dir::down:  return Dir::up;
    case Dir::left:  return Dir::right;
    default:         return Dir::none;
  }
}

constexpr Dir rotateCW(const Dir dir) {
  switch (dir) {
    case Dir::up:    return Dir::right;
    case Dir::right: return Dir::down;
    case Dir::down:  return Dir::left;
    case Dir::left:  return Dir::up;
    default:         return Dir::none;
  }
}

// Overloading increment and dereference operators to make Dir work as an
// iterator in range-for loops. Dir is an iterator for itself. This isn't a
// proper iterator. It's just the bare minimum to work with a range for loop.
// Take the following snippet:
//
// for (const Dir dir : dir_range) {
//    ...
// }
//
// This is de-sugared by the compiler into something like this:
//
// {
//   auto begin = dir_range.begin();
//   auto end = dir_range.end();
//   for (; begin != end; ++begin) {
//     const Dir dir = *begin;
//     ...
//   }
// }

constexpr Dir &operator++(Dir &dir) {
  return dir = static_cast<Dir>(static_cast<int>(dir) + 1);
}

constexpr Dir operator*(const Dir dir) {
  return dir;
}

struct DirRange {
  constexpr Dir begin() const {
    return Dir::begin;
  }

  constexpr Dir end() const {
    return Dir::end;
  }
};

constexpr DirRange dir_range{};

#endif
