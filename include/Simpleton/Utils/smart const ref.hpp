//
//  smart const ref.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_smart_const_ref_hpp
#define engine_utils_smart_const_ref_hpp

#include <type_traits>

namespace Utils {
  namespace detail {
    template <typename T>
    struct SmartConstRef {
      using type = std::conditional_t<
        std::is_trivially_copyable_v<T> && sizeof(T) <= 2 * sizeof(void *),
        const T,
        const T &
      >;
    };
  }
  
  template <typename T>
  using SmartConstRef = typename detail::SmartConstRef<T>::type;
}

#endif
