//
//  partial apply.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 26/10/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_partial_apply_hpp
#define engine_utils_partial_apply_hpp

#include <functional>

namespace Utils {
  template <typename Element, typename Compare>
  constexpr auto compare_to(Compare &&compare, const Element &elem) {
    return [comp = std::forward<Compare>(compare), elem] (const Element &other) -> bool {
      return comp(other, elem);
    };
  }

  template <typename Element>
  auto equal_to(const Element &elem) {
    return compare_to(std::equal_to<Element>{}, elem);
  }
  
  template <typename Element>
  auto not_equal_to(const Element &elem) {
    return compare_to(std::not_equal_to<Element>{}, elem);
  }
  
  template <typename Element>
  auto less_than(const Element &elem) {
    return compare_to(std::less<Element>{}, elem);
  }
  
  template <typename Element>
  auto greater_than(const Element &elem) {
    return compare_to(std::greater<Element>{}, elem);
  }
}

#endif
