//
//  numeric iterators.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 12/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_numeric_iterators_hpp
#define engine_utils_numeric_iterators_hpp

#include <iterator>

namespace Utils {
  template <typename Number, Number Step = 1>
  class AddingIterator {
  public:
    static_assert(Step != 0, "Step cannot be zero");
  
    using difference_type = Number;
    using value_type = Number;
    using reference = const value_type &;
    using pointer = const value_type *;
    using iterator_category = std::input_iterator_tag;
    
    constexpr explicit AddingIterator(const value_type value)
      : value(value) {}
    
    constexpr bool operator==(const AddingIterator other) const {
      return value == other.value;
    }
    constexpr bool operator!=(const AddingIterator other) const {
      return value != other.value;
    }
    
    constexpr AddingIterator &operator++() {
      value += Step;
      return *this;
    }
    constexpr AddingIterator operator++(int) {
      AddingIterator copy = *this;
      value += Step;
      return copy;
    }
    
    constexpr value_type operator*() const {
      return value;
    }
    
  private:
    value_type value;
  };
  
  template <typename Iter>
  class Range {
  public:
    constexpr Range(const Iter begin, const Iter end)
      : begin_{begin}, end_{end} {}
  
    constexpr Iter begin() const noexcept {
      return begin_;
    }
    constexpr Iter end() const noexcept {
      return end_;
    }
  
  private:
    Iter begin_;
    Iter end_;
  };
  
  template <typename Number>
  constexpr auto range(const Number begin, const Number end) {
    using Iterator = AddingIterator<Number>;
    return Range{
      Iterator{begin}, Iterator{end}
    };
  }
  
  template <typename Number>
  constexpr auto range(const Number size) {
    return range(Number{0}, size);
  }
  
  template <typename Number>
  constexpr auto rangeRev(const Number begin, const Number end) {
    using Iterator = AddingIterator<Number, Number{0} - Number{1}>;
    return Range{
      Iterator{end - Number{1}}, Iterator{begin - Number{1}}
    };
  }
  
  template <typename Number>
  constexpr auto rangeRev(const Number size) {
    return rangeRev(Number{0}, size);
  }
}

#endif
