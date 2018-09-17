//
//  reduce.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 6/7/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_reduce_hpp
#define engine_type_list_reduce_hpp

#include "type.hpp"

namespace List {
  // Reduce type
  
  namespace detail {
    template <typename List, typename Init, template <typename, typename> typename Operation>
    struct ReduceTypeI;
    
    template <typename Init, template <typename, typename> typename Operation>
    struct ReduceTypeI<EmptyType, Init, Operation> {
      using type = Init;
    };
    
    template <typename Init, template <typename, typename> typename Operation, typename First, typename... Types>
    struct ReduceTypeI<Type<First, Types...>, Init, Operation> {
      using type = typename ReduceTypeI<
        Type<Types...>, typename Operation<Init, First>::type, Operation
      >::type;
    };
    
    template <typename Prev, typename Curr>
    struct NestPair {
      using type = std::pair<Prev, Curr>;
    };
  }
  
  /// Apply an operation to each type in the type list and accumulate a type.
  template <typename List, typename Init, template <typename, typename> typename Operation>
  using ReduceT = typename detail::ReduceTypeI<List, Init, Operation>::type;
  
  static_assert(Same<ReduceT<Type<>, std::pair<int, int>, detail::NestPair>, std::pair<int, int>>);
  static_assert(Same<ReduceT<Type<char>, std::pair<int, int>, detail::NestPair>, std::pair<std::pair<int, int>, char>>);
  static_assert(Same<ReduceT<Type<char, long>, std::pair<int, int>, detail::NestPair>, std::pair<std::pair<std::pair<int, int>, char>, long>>);
  
  // Reduce value
  
  namespace detail {
    template <typename List, auto Init, template <auto, typename> typename Operation>
    struct ReduceValueI;
    
    template <auto Init, template <auto, typename> typename Operation>
    struct ReduceValueI<EmptyType, Init, Operation> {
      static constexpr auto value = Init;
    };
    
    template <auto Init, template <auto, typename> typename Operation, typename First, typename... Types>
    struct ReduceValueI<Type<First, Types...>, Init, Operation> {
      static constexpr auto value = ReduceValueI<
        Type<Types...>, Operation<Init, First>::value, Operation
      >::value;
    };
    
    template <size_t Size, typename T>
    struct MaxSize {
      static constexpr size_t value = sizeof(T) > Size ? sizeof(T) : Size;
    };
  }
  
  /// Apply an operation to each type in the type list and accumulate a value.
  template <typename List, auto Init, template <auto, typename> typename Operation>
  constexpr auto ReduceV = detail::ReduceValueI<List, Init, Operation>::value;
  
  static_assert(ReduceV<Type<>, 0, detail::MaxSize> == 0);
  static_assert(ReduceV<Type<int>, 0, detail::MaxSize> == sizeof(int));
  static_assert(ReduceV<Type<char[1], char[2], char[3]>, 0, detail::MaxSize> == sizeof(char[3]));
}

#endif
