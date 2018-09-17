//
//  type.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_type_hpp
#define engine_type_list_type_hpp

#include <cstddef>

namespace List {
  /// A type list
  template <typename... Types>
  struct Type {};
  
  /// An empty type list
  using EmptyType = Type<>;
  
  namespace detail {
    template <typename T, typename U>
    struct SameI {
      static constexpr bool value = false;
    };
    
    template <typename T>
    struct SameI<T, T> {
      static constexpr bool value = true;
    };
  }
  
  /// Are the given types the same?
  template <typename T, typename U>
  constexpr bool Same = detail::SameI<T, U>::value;
  
  // Empty
  
  /// Is this type list empty?
  template <typename List>
  constexpr bool Empty = Same<List, EmptyType>;
  
  static_assert(Empty<Type<>>);
  static_assert(!Empty<Type<int>>);
  
  // Size

  namespace detail {
    template <typename List>
    struct SizeI;
    
    template <typename... Types>
    struct SizeI<Type<Types...>> {
      static constexpr size_t value = sizeof...(Types);
    };
  }
  
  /// The number of types in a type list
  template <typename List>
  constexpr size_t Size = detail::SizeI<List>::value;
  
  static_assert(Size<Type<int, char, long>> == 3);
  static_assert(Size<Type<int>> == 1);
  static_assert(Size<Type<>> == 0);
  
  // Byte Size
  
  namespace detail {
    template <typename List>
    struct ByteSizeI;
    
    template <typename... Types>
    struct ByteSizeI<Type<Types...>> {
      static constexpr size_t value = (sizeof(Types) + ... + 0);
    };
  }
  
  /// The total size in bytes of all of the types
  template <typename List>
  constexpr size_t ByteSize = detail::ByteSizeI<List>::value;
  
  static_assert(ByteSize<EmptyType> == 0);
  static_assert(ByteSize<Type<int>> == sizeof(int));
  static_assert(ByteSize<Type<int, char, long>> == sizeof(int) + sizeof(char) + sizeof(long));
}

#endif
