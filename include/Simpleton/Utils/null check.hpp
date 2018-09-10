//
//  null check.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_null_check_hpp
#define engine_utils_null_check_hpp

#include <exception>

namespace Utils {
  class NullPointerError final : public std::exception {
  public:
    NullPointerError() = default;
    
    const char *what() const noexcept override {
      return "Null pointer error";
    }
  };

  template <typename Type>
  const Type *zeroIfNull(const Type *const ptr) noexcept {
    static const Type ZERO {};
    return ptr == nullptr ? &ZERO : ptr;
  }

  template <typename Type>
  void throwIfNull(const Type *const ptr) {
    if (ptr == nullptr) {
      throw NullPointerError();
    }
  }
}

#endif
