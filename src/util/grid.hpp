//
//  grid.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 8/5/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#ifndef UTIL_GRID_HPP
#define UTIL_GRID_HPP

#include <vector>
#include <cassert>
#include <utility>
#include "pos.hpp"

template <typename Elem>
class Grid {
public:
  Grid()
    : size{0, 0}, storage{} {}

  explicit Grid(const Pos size)
    : size{size}, storage(area()) {}

  int area() const {
    return size.x * size.y;
  }

  int width() const {
    return size.x;
  }

  int height() const {
    return size.y;
  }

  bool outOfRange(const std::size_t i) const {
    return i >= area();
  }

  bool outOfRange(const Pos pos) const {
    return pos.x < 0 || pos.y < 0 ||
           pos.x >= size.x || pos.y >= size.y;
  }

  Elem &operator[](const std::size_t i) {
    return const_cast<Elem &>(std::as_const(*this)[i]);
  }

  Elem &operator[](const Pos pos) {
    return const_cast<Elem &>(std::as_const(*this)[pos]);
  }

  const Elem &operator[](const std::size_t i) const {
    assert(!outOfRange(i));
    return storage[i];
  }

  const Elem &operator[](const Pos pos) const {
    assert(!outOfRange(pos));
    return storage[pos.y * size.x + pos.x];
  }

private:
  Pos size;
  std::vector<Elem> storage;
};

#endif
