//
//  strong alias.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 16/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_strong_alias_hpp
#define engine_utils_strong_alias_hpp

#include <type_traits>

namespace Utils {
  template <typename T, typename Group = void>
  struct StrongAlias {
    using value_type = T;
    
    StrongAlias() = default;
    StrongAlias(const StrongAlias &) = default;
    StrongAlias(StrongAlias &&) = default;
    ~StrongAlias() = default;
    StrongAlias &operator=(const StrongAlias &) = default;
    StrongAlias &operator=(StrongAlias &&) = default;
    
    explicit StrongAlias(const T val)
      : val(val) {}
    
    template <typename U>
    explicit StrongAlias(const U val)
      : val(static_cast<T>(val)) {}
    
    template <typename OtherT, typename OtherGroup>
    explicit StrongAlias(const StrongAlias<OtherT, OtherGroup> other)
      : val(static_cast<T>(other.val)) {}
    
    explicit operator T() const {
      return val;
    }
    
    template <typename U>
    explicit operator U() const {
      return static_cast<U>(val);
    }
    
    template <typename OtherT, typename OtherGroup>
    explicit operator StrongAlias<OtherT, OtherGroup>() const {
      return StrongAlias<OtherT, OtherGroup>(static_cast<OtherT>(val));
    }
    
    decltype(!std::declval<const T>()) operator!() const {
      return !val;
    }
    decltype(~std::declval<const T>()) operator~() const {
      return ~val;
    }
    
    decltype(++std::declval<T &>()) operator++() {
      return ++val;
    }
    decltype(--std::declval<T &>()) operator--() {
      return --val;
    }
    
    decltype(std::declval<T &>()++) operator++(int) {
      return val++;
    }
    decltype(std::declval<T &>()--) operator--(int) {
      return val--;
    }
    
    template <typename U>
    decltype(std::declval<const T>()[std::declval<U>()]) operator[](const U i) const {
      return val[i];
    }
    template <typename U>
    decltype(std::declval<T>()[std::declval<U>()]) operator[](const U i) {
      return val[i];
    }
    
    T val;
  };
  
  
  template <typename Type>
  struct IsStrongAlias : std::false_type {};

  template <typename T, typename Group>
  struct IsStrongAlias<StrongAlias<T, Group>> : std::true_type {};
}

template <typename T, typename Ret, typename Group>
struct GetRetType {
  using type = Ret;
};

template <typename T, typename Group>
struct GetRetType<T, T, Group> {
  using type = Utils::StrongAlias<T, Group>;
};

template <typename T, typename Group>
struct GetRetType<T, T &, Group> {
  using type = Utils::StrongAlias<T, Group> &;
};

template <typename T, typename Ret, typename Group>
using RetType = typename GetRetType<T, Ret, Group>::type;

#define RET_TYPE(LEFT, RIGHT, RET, OP, GROUP)                                   \
RetType<RET, decltype(std::declval<LEFT>() OP std::declval<RIGHT>()), GROUP>

#define BIN_OP(OP)                                                              \
template <typename T, typename Group>                                           \
RET_TYPE(T, T, T, OP, Group)                                                    \
operator OP(                                                                    \
  const Utils::StrongAlias<T, Group> left,                                      \
  const Utils::StrongAlias<T, Group> right                                      \
) {                                                                             \
  return RET_TYPE(T, T, T, OP, Group)(left.val OP right.val);                   \
}                                                                               \
template <typename Left, typename Right, typename Group>                        \
std::enable_if_t<                                                               \
  !Utils::IsStrongAlias<Right>::value,                                          \
  RET_TYPE(Left, Right, Left, OP, Group)                                        \
>                                                                               \
operator OP(const Utils::StrongAlias<Left, Group> left, const Right right) {    \
  return RET_TYPE(Left, Right, Left, OP, Group)(left.val OP right);             \
}                                                                               \
template <typename Left, typename Right, typename Group>                        \
std::enable_if_t<                                                               \
  !Utils::IsStrongAlias<Left>::value,                                           \
  RET_TYPE(Left, Right, Right, OP, Group)                                       \
>                                                                               \
operator OP(const Left left, const Utils::StrongAlias<Right, Group> right) {    \
  return RET_TYPE(Left, Right, Right, OP, Group)(left OP right.val);            \
}

BIN_OP(==)
BIN_OP(!=)
BIN_OP(<)
BIN_OP(>)
BIN_OP(<=)
BIN_OP(>=)
BIN_OP(&&)
BIN_OP(||)
BIN_OP(+)
BIN_OP(-)
BIN_OP(*)
BIN_OP(/)
BIN_OP(%)
BIN_OP(&)
BIN_OP(|)
BIN_OP(^)
BIN_OP(<<)
BIN_OP(>>)

#undef BIN_OP

#define ASSIGN_OP(OP)                                                           \
template <typename T, typename Group>                                           \
RET_TYPE(T &, T, T, OP, Group)                                                  \
operator OP(                                                                    \
  Utils::StrongAlias<T, Group> &left,                                           \
  const Utils::StrongAlias<T, Group> right                                      \
) {                                                                             \
  return RET_TYPE(T &, T, T, OP, Group)(left.val OP right.val);                 \
}                                                                               \
template <typename Left, typename Right, typename Group>                        \
std::enable_if_t<                                                               \
  !Utils::IsStrongAlias<Right>::value,                                          \
  RET_TYPE(Left &, Right, Left, OP, Group)                                      \
>                                                                               \
operator OP(Utils::StrongAlias<Left, Group> &left, const Right right) {         \
  return RET_TYPE(Left &, Right, Left, OP, Group)(left.val OP right);           \
}                                                                               \
template <typename Left, typename Right, typename Group>                        \
std::enable_if_t<                                                               \
  !Utils::IsStrongAlias<Left>::value,                                           \
  RET_TYPE(Left &, Right, Right, OP, Group)                                     \
>                                                                               \
operator OP(Left &left, const Utils::StrongAlias<Right, Group> right) {         \
  return RET_TYPE(Left &, Right, Right, OP, Group)(left OP right.val);          \
}

ASSIGN_OP(+=)
ASSIGN_OP(-=)
ASSIGN_OP(*=)
ASSIGN_OP(/=)
ASSIGN_OP(%=)
ASSIGN_OP(&=)
ASSIGN_OP(|=)
ASSIGN_OP(^=)
ASSIGN_OP(<<=)
ASSIGN_OP(>>=)

#undef ASSIGN_OP
#undef RET_TYPE

#endif
