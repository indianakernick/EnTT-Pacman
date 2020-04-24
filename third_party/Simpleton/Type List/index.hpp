//
//  index.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_index_hpp
#define engine_type_list_index_hpp

#include "type.hpp"

namespace List {
  // At Index
  
  namespace detail {
    template <typename List, size_t Index>
    struct AtIndexI {
      static_assert(!Empty<List>, "Index out of range");
    };
    
    template <size_t Index, typename FirstType, typename... Types>
    struct AtIndexI<Type<FirstType, Types...>, Index> {
      using type = typename AtIndexI<Type<Types...>, Index - 1>::type;
    };
    
    template <typename First, typename... Types>
    struct AtIndexI<Type<First, Types...>, 0> {
      using type = First;
    };
  }
  
  /// The type at an index of a type list. Compile-time error if index is out
  /// of range
  template <typename List, size_t Index>
  using AtIndex = typename detail::AtIndexI<List, Index>::type;
  
  /// The type at an index from the end of a type list. Compile-time error if
  /// index is out of range
  template <typename List, size_t Index>
  using AtIndexRev = typename detail::AtIndexI<List, Size<List> - Index - 1>::type;
  
  static_assert(Same<AtIndex<Type<int, char, long>, 0>, int>);
  static_assert(Same<AtIndex<Type<int, char, long>, 1>, char>);
  static_assert(Same<AtIndex<Type<int, char, long>, 2>, long>);
  
  // Index Of
  
  constexpr size_t npos = size_t(-1);
  
  namespace detail {
    template <typename List, typename Type, size_t Index = 0>
    struct IndexOfI;
    
    template <typename T, typename... Types, size_t Index>
    struct IndexOfI<Type<T, Types...>, T, Index> {
      static constexpr size_t value = Index;
    };
    
    template <typename T, typename FirstType, typename... Types, size_t Index>
    struct IndexOfI<Type<FirstType, Types...>, T, Index> {
      static constexpr size_t value = IndexOfI<Type<Types...>, T, Index + 1>::value;
    };
    
    template <typename T, size_t Index>
    struct IndexOfI<EmptyType, T, Index> {
      static constexpr size_t value = npos;
    };
  }
  
  /// The index of the type in the list. npos if the type is not in the list
  template <typename List, typename Type>
  constexpr size_t IndexOf = detail::IndexOfI<List, Type>::value;
  
  static_assert(IndexOf<EmptyType, int> == npos);
  static_assert(IndexOf<Type<int>, int> == 0);
  static_assert(IndexOf<Type<int, char, long>, int> == 0);
  static_assert(IndexOf<Type<int, char, long>, char> == 1);
  static_assert(IndexOf<Type<int, char, long>, long> == 2);
  static_assert(IndexOf<Type<int, char, long>, float> == npos);
  
  /// True if the list has the given type
  template <typename List, typename Type>
  constexpr bool Has = IndexOf<List, Type> != npos;
}

#endif
