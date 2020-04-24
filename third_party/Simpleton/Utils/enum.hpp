//
//  enum.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_enum_hpp
#define engine_utils_enum_hpp

#include <type_traits>

namespace Utils::Operators {
  template <typename Enum>
  constexpr auto operator+(const Enum e) -> std::underlying_type_t<Enum> {
    return static_cast<std::underlying_type_t<Enum>>(e);
  }
}

#endif
