//
//  pred.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_pred_hpp
#define engine_type_list_pred_hpp

#include "concat.hpp"

namespace List {
  namespace detail {
    template <typename T>
    struct IsIntegral {
      static constexpr bool value = false;
    };
    template <>
    struct IsIntegral<char> {
      static constexpr bool value = true;
    };
    template <>
    struct IsIntegral<int> {
      static constexpr bool value = true;
    };
    template <>
    struct IsIntegral<long> {
      static constexpr bool value = true;
    };
  }
  
  // Count
  
  namespace detail {
    template <typename List, template <typename> typename Pred>
    struct CountI;
    
    template <template <typename> typename Pred, typename... Types>
    struct CountI<Type<Types...>, Pred> {
      static constexpr size_t value = (bool(Pred<Types>::value) + ... + 0);
    };
  }
  
  /// How many types satisfy the predicate?
  template <typename List, template <typename> typename Pred>
  constexpr size_t Count = detail::CountI<List, Pred>::value;

  // All
  
  /// Do all of the types satisfy the predicate?
  template <typename List, template <typename> typename Pred>
  constexpr bool All = Count<List, Pred> == Size<List>;
  
  static_assert(All<EmptyType, detail::IsIntegral>);
  static_assert(All<Type<int, char, long>, detail::IsIntegral>);
  static_assert(!All<Type<int, float, char, double>, detail::IsIntegral>);
  
  // Any
  
  /// Do any of the types satisfy the predicate?
  template <typename List, template <typename> typename Pred>
  constexpr bool Any = Count<List, Pred> > 0;
  
  static_assert(!Any<EmptyType, detail::IsIntegral>);
  static_assert(Any<Type<int, float, char, double>, detail::IsIntegral>);
  static_assert(!Any<Type<float, double>, detail::IsIntegral>);
  
  // None
  
  /// Do none of the types satisfy the predicate?
  template <typename List, template <typename> typename Pred>
  constexpr bool None = Count<List, Pred> == 0;
  
  static_assert(None<EmptyType, detail::IsIntegral>);
  static_assert(None<Type<float, double>, detail::IsIntegral>);
  static_assert(!None<Type<int, float, char, double>, detail::IsIntegral>);
  
  // Filter
  
  namespace detail {
    template <typename T, bool Pred>
    struct FilterOne {
      using type = Type<T>;
    };
    
    template <typename T>
    struct FilterOne<T, false> {
      using type = EmptyType;
    };
  
    template <typename List, template <typename> typename Pred>
    struct FilterI;
    
    template <template <typename> typename Pred, typename First, typename... Types>
    struct FilterI<Type<First, Types...>, Pred> {
      using type = Concat<
        typename FilterOne<First, Pred<First>::value>::type,
        typename FilterI<Type<Types...>, Pred>::type
      >;
    };
    
    template <template <typename> typename Pred>
    struct FilterI<EmptyType, Pred> {
      using type = EmptyType;
    };
  }
  
  /// Create a list of types that satisfy the predicate. Pred must be a struct
  /// that takes a single type and has a value member
  template <typename List, template <typename> typename Pred>
  using Filter = typename detail::FilterI<List, Pred>::type;
  
  static_assert(Same<Filter<Type<int, char, float, long, double>, detail::IsIntegral>, Type<int, char, long>>);
}

#endif
