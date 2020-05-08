//
//  grid.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 8/5/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//

#ifndef UTIL_GRID_HPP
#define UTIL_GRID_HPP

#include <vector>
#include <cassert>
#include "pos.hpp"
#include "int_range.hpp"

template <typename Elem>
class Grid {
public:
  using value_type = Elem;
  using reference = value_type &;
  using const_reference = const value_type &;

  Grid()
    : size_{0, 0}, storage_{} {}
  explicit Grid(const Pos size)
    : size_{size}, storage_(area()) {}

  int area() const {
    return size_.x * size_.y;
  }

  IntRange<int> hori() const {
    return {0, size_.x};
  }
  IntRange<int> vert() const {
    return {0, size_.y};
  }

  bool outOfRange(const std::size_t i) const {
    return i >= area();
  }
  bool outOfRange(const Pos pos) const {
    return pos.x < 0 || pos.y < 0 ||
           pos.x >= size_.x || pos.y >= size_.y;
  }

  reference operator[](const std::size_t i) {
    return const_cast<reference>(std::as_const(*this)[i]);
  }
  reference operator[](const Pos pos) {
    return const_cast<reference>(std::as_const(*this)[pos]);
  }

  const_reference operator[](const std::size_t i) const {
    assert(!outOfRange(i));
    return storage_[i];
  }
  const_reference operator[](const Pos pos) const {
    assert(!outOfRange(pos));
    return storage_[pos.y * size_.x + pos.x];
  }

private:
  Pos size_;
  std::vector<value_type> storage_;
};

#endif