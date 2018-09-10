//
//  concat.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_concat_hpp
#define engine_type_list_concat_hpp

#include "type.hpp"

namespace List {
  // Concat

  namespace detail {
    template <typename... Lists>
    struct ConcatI;
    
    template <>
    struct ConcatI<> {
      using type = EmptyType;
    };
    
    template <typename... Types>
    struct ConcatI<Type<Types...>> {
      using type = Type<Types...>;
    };
    
    template <typename... LeftTypes, typename... RightTypes>
    struct ConcatI<Type<LeftTypes...>, Type<RightTypes...>> {
      using type = Type<LeftTypes..., RightTypes...>;
    };
    
    template <typename FirstList, typename... Lists>
    struct ConcatI<FirstList, Lists...> {
      using type = typename ConcatI<FirstList, typename ConcatI<Lists...>::type>::type;
    };
  }
  
  /// Concatenate the given lists into one
  template <typename... Lists>
  using Concat = typename detail::ConcatI<Lists...>::type;
  
  static_assert(Same<Concat<Type<int, char>, Type<long>>, Type<int, char, long>>);
  static_assert(Same<Concat<Type<int, char, long>, EmptyType>, Type<int, char, long>>);
  static_assert(Same<Concat<EmptyType, EmptyType>, EmptyType>);
  
  // First
  
  namespace detail {
    template <typename List>
    struct FirstI {
      static_assert(!Empty<List>, "Cannot get first type of empty List");
    };
    
    template <typename FirstType, typename... Types>
    struct FirstI<Type<FirstType, Types...>> {
      using type = FirstType;
    };
  }
  
  /// The first type of the list. Compile-time error if the list is empty
  template <typename List>
  using First = typename detail::FirstI<List>::type;
  
  // Last
  
  namespace detail {
    template <typename List>
    struct LastI {
      static_assert(!Empty<List>, "Cannot get last type of empty List");
    };
    
    template <typename LastType>
    struct LastI<Type<LastType>> {
      using type = LastType;
    };
    
    template <typename LastType, typename... Types>
    struct LastI<Type<LastType, Types...>> {
      using type = typename LastI<Type<Types...>>::type;
    };
  }
  
  /// The last type of the list. Compile-time error if the list is empty
  template <typename List>
  using Last = typename detail::LastI<List>::type;
  
  static_assert(Same<Last<Type<int, char, long>>, long>);
}

#endif
