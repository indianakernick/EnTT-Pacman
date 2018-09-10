//
//  foreach.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_foreach_hpp
#define engine_type_list_foreach_hpp

#include "type.hpp"

namespace List {
  namespace detail {
    template <typename T>
    struct TypeObj {
      using type = T;
    };
    
    #define LIST_TYPE(OBJ) typename decltype(OBJ)::type
    
    template <typename List>
    struct ForEachI;
    
    template <typename... Types>
    struct ForEachI<Type<Types...>> {
      template <typename Function>
      static constexpr void iter(Function &&function) {
        (function(TypeObj<Types>()), ...);
      }
    };
  }
  
  /// Call the given template function (or lambda) for each type in the list.
  /// The function is called with an instance of List::detail::TypeObj which has
  /// a `type` member
  template <typename List, typename Function>
  constexpr void forEach(Function &&function) {
    detail::ForEachI<List>::iter(static_cast<Function &&>(function));
  }
  
  /// An index list
  template <size_t... Indicies>
  struct Index {};
  
  /// An empty index list
  using EmptyIndex = Index<>;
  
  namespace detail {
    template <size_t... Ints>
    struct MakeIndexListI;
    
    template <size_t First, size_t... Ints>
    struct MakeIndexListI<First, Ints...> {
      using type = typename MakeIndexListI<First - 1, First - 1, Ints...>::type;
    };
    
    template <size_t... Ints>
    struct MakeIndexListI<0, Ints...> {
      using type = Index<Ints...>;
    };
  }
  
  /// Make an index list of the given size
  template <size_t Size>
  using MakeIndexList = typename detail::MakeIndexListI<Size>::type;
  
  static_assert(Same<MakeIndexList<0>, EmptyIndex>);
  static_assert(Same<MakeIndexList<1>, Index<0>>);
  static_assert(Same<MakeIndexList<2>, Index<0, 1>>);
  static_assert(Same<MakeIndexList<3>, Index<0, 1, 2>>);
  
  namespace detail {
    template <size_t I>
    struct IndexObj {
      static constexpr size_t value = I;
    };
    
    #define LIST_VALUE(OBJ) decltype(OBJ)::value
    
    template <typename List>
    struct ForEachIndexI;
    
    template <size_t... Ints>
    struct ForEachIndexI<Index<Ints...>> {
      template <typename Function>
      static constexpr void iter(Function &&function) {
        (function(IndexObj<Ints>()), ...);
      }
    };
  }
  
  /// Call the given template function (or lambda) for each index in the list.
  /// The function is called with an instance of List::detail::IndexObj which
  /// has a `value` member
  template <typename List, typename Function>
  constexpr void forEachIndex(Function &&function) {
    detail::ForEachIndexI<List>::iter(static_cast<Function &&>(function));
  }
  
  template <size_t Size, typename Function>
  constexpr void forEachIndex(Function &&function) {
    forEachIndex<MakeIndexList<Size>>(static_cast<Function &&>(function));
  }
}

#endif
