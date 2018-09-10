//
//  function alias.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_function_alias_hpp
#define engine_utils_function_alias_hpp

#include <utility>

/// Create a function alias using a function pointer
#define FUN_ALIAS_PTR(NEW_NAME, ...)                                            \
  constexpr auto NEW_NAME = __VA_ARGS__;

/// Create a function alias with specifiers
#define FUN_ALIAS_SPEC(SPECS, NEW_NAME, ...)                                    \
  template <typename... Args>                                                   \
  SPECS auto NEW_NAME(Args &&... args)                                          \
    noexcept(noexcept(__VA_ARGS__(std::forward<Args>(args)...)))                \
    -> decltype(__VA_ARGS__(std::forward<Args>(args)...)) {                     \
    return __VA_ARGS__(std::forward<Args>(args)...);                            \
  }

/// Create a function alias
#define FUN_ALIAS(NEW_NAME, ...)                                                \
  FUN_ALIAS_SPEC(inline, NEW_NAME, __VA_ARGS__)

#endif
