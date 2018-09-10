//
//  generic raii.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 23/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_generic_raii_hpp
#define engine_utils_generic_raii_hpp

#include <utility>
#include <type_traits>

// Same interface as std::unique_ptr (the best class in the entire STL)

#define UTILS_RAII_CLASS_BASIC(CLASS, TYPE, MEMBER, DELETE)                     \
  using value_type = TYPE;                                                      \
                                                                                \
  constexpr CLASS() noexcept                                                    \
    : MEMBER{} {}                                                               \
  constexpr CLASS(std::nullptr_t) noexcept                                      \
    : MEMBER{} {}                                                               \
  explicit CLASS(const value_type MEMBER) noexcept                              \
    : MEMBER{MEMBER} {}                                                         \
  CLASS(CLASS &&other) noexcept                                                 \
    : MEMBER{other.release()} {}                                                \
  CLASS &operator=(CLASS &&other) noexcept {                                    \
    reset(other.release());                                                     \
    return *this;                                                               \
  }                                                                             \
  CLASS &operator=(std::nullptr_t) noexcept {                                   \
    reset();                                                                    \
    return *this;                                                               \
  }                                                                             \
  ~CLASS() {                                                                    \
    DELETE(MEMBER);                                                             \
  }                                                                             \
                                                                                \
  value_type release() noexcept {                                               \
    return std::exchange(MEMBER, value_type{});                                 \
  }                                                                             \
  void reset(const value_type new##MEMBER = {}) noexcept {                      \
    DELETE(MEMBER);                                                             \
    MEMBER = new##MEMBER;                                                       \
  }                                                                             \
                                                                                \
  value_type get() const noexcept {                                             \
    return MEMBER;                                                              \
  }                                                                             \
  explicit operator bool() const noexcept {                                     \
    return MEMBER != value_type{};                                              \
  }                                                                             \

#define UTILS_RAII_CLASS_COMPARISON(CLASS, MEMBER)                              \
  bool operator==(const CLASS &other) const noexcept {                          \
    return MEMBER == other.MEMBER;                                              \
  }                                                                             \
  bool operator!=(const CLASS &other) const noexcept {                          \
    return MEMBER != other.MEMBER;                                              \
  }                                                                             \
  bool operator<(const CLASS &other) const noexcept {                           \
    return MEMBER < other.MEMBER;                                               \
  }                                                                             \
  bool operator<=(const CLASS &other) const noexcept {                          \
    return MEMBER <= other.MEMBER;                                              \
  }                                                                             \
  bool operator>(const CLASS &other) const noexcept {                           \
    return MEMBER > other.MEMBER;                                               \
  }                                                                             \
  bool operator>=(const CLASS &other) const noexcept {                          \
    return MEMBER >= other.MEMBER;                                              \
  }                                                                             \

#define UTILS_RAII_CLASS_NULL_COMPARISON(CLASS, MEMBER)                         \
  friend bool operator==(const CLASS &obj, std::nullptr_t) noexcept {           \
    return obj.MEMBER == value_type{};                                          \
  }                                                                             \
  friend bool operator!=(const CLASS &obj, std::nullptr_t) noexcept {           \
    return obj.MEMBER != value_type{};                                          \
  }                                                                             \
  /* suppressing warnings */                                                    \
  friend bool operator<(const CLASS &obj, std::nullptr_t) noexcept {            \
    if constexpr (std::is_unsigned_v<value_type>) {                             \
      return false;                                                             \
    } else {                                                                    \
      return obj.MEMBER < value_type{};                                         \
    }                                                                           \
  }                                                                             \
  friend bool operator<=(const CLASS &obj, std::nullptr_t) noexcept {           \
    return obj.MEMBER <= value_type{};                                          \
  }                                                                             \
  friend bool operator>(const CLASS &obj, std::nullptr_t) noexcept {            \
    return obj.MEMBER > value_type{};                                           \
  }                                                                             \
  /* suppressing warnings */                                                    \
  friend bool operator>=(const CLASS &obj, std::nullptr_t) noexcept {           \
    if constexpr (std::is_unsigned_v<value_type>) {                             \
      return true;                                                              \
    } else {                                                                    \
      return obj.MEMBER >= value_type{};                                        \
    }                                                                           \
  }                                                                             \
                                                                                \
  friend bool operator==(std::nullptr_t, const CLASS &obj) noexcept {           \
    return value_type{} == obj.MEMBER;                                          \
  }                                                                             \
  friend bool operator!=(std::nullptr_t, const CLASS &obj) noexcept {           \
    return value_type{} != obj.MEMBER;                                          \
  }                                                                             \
  friend bool operator<(std::nullptr_t, const CLASS &obj) noexcept {            \
    return value_type{} < obj.MEMBER;                                           \
  }                                                                             \
  /* suppressing warnings */                                                    \
  friend bool operator<=(std::nullptr_t, const CLASS &obj) noexcept {           \
    if constexpr (std::is_unsigned_v<value_type>) {                             \
      return true;                                                              \
    } else {                                                                    \
      return value_type{} <= obj.MEMBER;                                        \
    }                                                                           \
  }                                                                             \
  /* suppressing warnings */                                                    \
  friend bool operator>(std::nullptr_t, const CLASS &obj) noexcept {            \
    if constexpr (std::is_unsigned_v<value_type>) {                             \
      return false;                                                             \
    } else {                                                                    \
      return value_type{} > obj.MEMBER;                                         \
    }                                                                           \
  }                                                                             \
  friend bool operator>=(std::nullptr_t, const CLASS &obj) noexcept {           \
    return value_type{} >= obj.MEMBER;                                          \
  }

#define UTILS_RAII_CLASS_SWAP(CLASS, MEMBER)                                    \
  void swap(CLASS &other) noexcept {                                            \
    std::swap(MEMBER, other.MEMBER);                                            \
  }                                                                             \
  friend void swap(CLASS &a, CLASS &b) noexcept {                               \
    std::swap(a.MEMBER, b.MEMBER);                                              \
  }

#define UTILS_RAII_CLASS_FULL(CLASS, TYPE, MEMBER, DELETE)                      \
  UTILS_RAII_CLASS_BASIC(CLASS, TYPE, MEMBER, DELETE)                           \
  UTILS_RAII_CLASS_COMPARISON(CLASS, MEMBER)                                    \
  UTILS_RAII_CLASS_NULL_COMPARISON(CLASS, MEMBER)                               \
  UTILS_RAII_CLASS_SWAP(CLASS, MEMBER)

#endif
