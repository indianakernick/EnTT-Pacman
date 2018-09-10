//
//  transform.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_transform_hpp
#define engine_type_list_transform_hpp

#include "concat.hpp"

namespace List {
  // Transform
  
  namespace detail {
    template <typename List, template <typename> typename Operation>
    struct TransformI;
    
    template <template <typename> typename Operation, typename... Types>
    struct TransformI<Type<Types...>, Operation> {
      using type = Type<typename Operation<Types>::type...>;
    };
    
    template <typename T>
    struct AddPointer {
      using type = T *;
    };
  }
  
  /// Apply an operation of each type in the list. Operation must be a struct
  /// that takes a single type and has a type member
  template <typename List, template <typename> typename Operation>
  using Transform = typename detail::TransformI<List, Operation>::type;
  
  static_assert(Same<Transform<Type<int, char, long>, detail::AddPointer>, Type<int *, char *, long *>>);
  static_assert(Same<Transform<EmptyType, detail::AddPointer>, EmptyType>);

  // Reverse

  namespace detail {
    template <typename List>
    struct ReverseI;
    
    template <>
    struct ReverseI<EmptyType> {
      using type = EmptyType;
    };
    
    template <typename T>
    struct ReverseI<Type<T>> {
      using type = Type<T>;
    };
    
    template <typename FirstType, typename... Types>
    struct ReverseI<Type<FirstType, Types...>> {
      using type = Concat<typename ReverseI<Type<Types...>>::type, Type<FirstType>>;
    };
  }
  
  /// Reverse the order of the types in the list
  template <typename List>
  using Reverse = typename detail::ReverseI<List>::type;

  static_assert(Same<
    Reverse<Type<int, char, float, long, double>>,
    Type<double, long, float, char, int>
  >);
  
  // Contains
  
  namespace detail {
    template <typename List, typename Type>
    struct ContainsI;
    
    template <typename T, typename... Types>
    struct ContainsI<Type<T, Types...>, T> {
      static constexpr bool value = true;
    };
    
    template <typename T, typename FirstType, typename... Types>
    struct ContainsI<Type<FirstType, Types...>, T> {
      static constexpr bool value = ContainsI<Type<Types...>, T>::value;
    };
    
    template <typename Type>
    struct ContainsI<EmptyType, Type> {
      static constexpr bool value = false;
    };
  }
  
  /// Does the list contain this type?
  template <typename List, typename Type>
  constexpr bool Contains = detail::ContainsI<List, Type>::value;
  
  static_assert(Contains<Type<int, char, long>, int>);
  static_assert(Contains<Type<int, char, long>, char>);
  static_assert(Contains<Type<int, char, long>, long>);
  static_assert(!Contains<Type<int, char, long>, float>);
}

#endif
