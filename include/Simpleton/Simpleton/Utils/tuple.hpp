//
//  tuple.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 1/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_tuple_hpp
#define engine_utils_tuple_hpp

#include <tuple>

namespace Utils {
  template <typename Type, typename Tuple, size_t ...Is>
  constexpr Type constructFromTupleHelper(Tuple &&tuple, std::index_sequence<Is...>) {
    return {std::get<Is>(std::forward<Tuple>(tuple))...};
  }
  
  template <typename Type, typename Tuple>
  constexpr Type constructFromTuple(Tuple &&tuple) {
    return constructFromTupleHelper<Type>(
      std::forward<Tuple>(tuple),
      std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>()
    );
  }
  
  template <typename Tuple, typename Function, size_t ...INDICIES>
  constexpr void forEachTupleHelper(Tuple &&tuple, Function &&function, std::index_sequence<INDICIES...>) {
    (function(std::get<INDICIES>(tuple)), ...);
  }
  
  template <typename Tuple, typename Function>
  constexpr void forEach(Tuple &&tuple, Function &&function) {
    forEachTupleHelper(
      std::forward<Tuple>(tuple),
      std::forward<Function>(function),
      std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>()
    );
  }
  
  #define UTILS_VALUE(OBJ) decltype(OBJ)::value
  
  template <typename Function, size_t ...INDICIES>
  constexpr void forEachIndexHelper(Function &&function, std::index_sequence<INDICIES...>) {
    (function(std::integral_constant<size_t, INDICIES>()), ...);
  }
  
  template <size_t SIZE, typename Function>
  constexpr void forEachIndex(Function &&function) {
    forEachIndexHelper(
      std::forward<Function>(function),
      std::make_index_sequence<SIZE>()
    );
  }
  
  template <typename Tuple>
  struct IsTuple : std::false_type {};
  template <typename ...Types>
  struct IsTuple<std::tuple<Types...>> : std::true_type {};
  
  template <typename T, typename U = void>
  struct IsTupleLike : std::false_type {};
  template <typename T>
  struct IsTupleLike<T, decltype((void)std::tuple_size<T>::value)> : std::true_type {};

  template <typename T>
  auto getElement(T &&element) {
    if constexpr (IsTuple<std::decay_t<T>>::value) {
      return std::forward<T>(element);
    } else {
      return std::forward_as_tuple(element);
    }
  }

  template <typename Tuple, size_t ...Is>
  auto flattenHelper(Tuple &&tuple, std::index_sequence<Is...>) {
    return std::tuple_cat(getElement(std::get<Is>(tuple))...);
  }

  template <typename Tuple>
  auto flatten(Tuple &&tuple) {
    return flattenHelper(
      tuple,
      std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>()
    );
  }
}

#endif
