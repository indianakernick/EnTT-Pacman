//
//  int_range.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 8/5/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//

#ifndef UTIL_INT_RANGE_HPP
#define UTIL_INT_RANGE_HPP

// This is the absolute bare minimum to work with range-for

template <typename Elem>
class IntIterator {
public:
  constexpr explicit IntIterator(const Elem pos)
    : pos{pos} {}

  constexpr IntIterator &operator++() {
    ++pos;
    return *this;
  }
  constexpr bool operator!=(const IntIterator &other) const {
    return pos != other.pos;
  }
  constexpr Elem operator*() const {
    return pos;
  }

private:
  Elem pos;
};

template <typename Elem>
class IntRange {
public:
  constexpr IntRange(const Elem begin, const Elem end)
    : begin_{begin}, end_{end} {}

  constexpr IntIterator<Elem> begin() const {
    return IntIterator{begin_};
  }
  constexpr IntIterator<Elem> end() const {
    return IntIterator{end_};
  }

private:
  Elem begin_, end_;
};

#endif
