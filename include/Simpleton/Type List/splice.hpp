//
//  splice.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_splice_hpp
#define engine_type_list_splice_hpp

#include "concat.hpp"

namespace List {
  // Push front
  
  namespace detail {
    template <typename List, typename T, size_t Num>
    struct PushFrontI {
      using type = typename PushFrontI<Concat<Type<T>, List>, T, Num - 1>::type;
    };
    
    template <typename List, typename Type>
    struct PushFrontI<List, Type, 0> {
      using type = List;
    };
  }

  /// Push one or more copies of a type onto the front of the list
  template <typename List, typename Type, size_t Num = 1>
  using PushFront = typename detail::PushFrontI<List, Type, Num>::type;
  
  static_assert(Same<PushFront<EmptyType, int, 0>, EmptyType>);
  static_assert(Same<PushFront<Type<char, long>, int, 0>, Type<char, long>>);
  static_assert(Same<PushFront<Type<char, long>, int, 1>, Type<int, char, long>>);
  static_assert(Same<PushFront<Type<char, long>, int, 2>, Type<int, int, char, long>>);
  static_assert(Same<PushFront<Type<char, long>, int, 3>, Type<int, int, int, char, long>>);
  
  // Pop front
  
  namespace detail {
    template <typename List>
    struct PopFrontOne;
    
    template <typename First, typename... Types>
    struct PopFrontOne<Type<First, Types...>> {
      using type = Type<Types...>;
    };
    
    template <>
    struct PopFrontOne<EmptyType> {
      using type = EmptyType;
    };
  
    template <typename List, size_t Num>
    struct PopFrontI {
      using type = typename PopFrontI<typename PopFrontOne<List>::type, Num - 1>::type;
    };
    
    template <typename List>
    struct PopFrontI<List, 0> {
      using type = List;
    };
  }
  
  /// Pop one or more types from the front of the list
  template <typename List, size_t Num = 1>
  using PopFront = typename detail::PopFrontI<List, Num>::type;
  
  static_assert(Same<PopFront<Type<int, char, long>, 0>, Type<int, char, long>>);
  static_assert(Same<PopFront<Type<int, char, long>, 1>, Type<char, long>>);
  static_assert(Same<PopFront<Type<int, char, long>, 2>, Type<long>>);
  static_assert(Same<PopFront<Type<int, char, long>, 3>, EmptyType>);
  static_assert(Same<PopFront<Type<int, char, long>, 4>, EmptyType>);
  static_assert(Same<PopFront<EmptyType, 0>, EmptyType>);
  static_assert(Same<PopFront<EmptyType, 1>, EmptyType>);

  // Take Front
  
  namespace detail {
    template <typename List, size_t Size>
    struct TakeFrontI {
      using type = Concat<
        Type<First<List>>,
        typename TakeFrontI<PopFront<List>, Size - 1>::type
      >;
    };
    
    template <typename List>
    struct TakeFrontI<List, 0> {
      using type = EmptyType;
    };
    
    template <size_t Size>
    struct TakeFrontI<EmptyType, Size> {
      using type = EmptyType;
    };
    
    template <>
    struct TakeFrontI<EmptyType, 0> {
      using type = EmptyType;
    };
  }
  
  /// Take a list of types from the front of the list
  template <typename List, size_t Size>
  using TakeFront = typename detail::TakeFrontI<List, Size>::type;
  
  static_assert(Same<TakeFront<Type<int, char, long>, 4>, Type<int, char, long>>);
  static_assert(Same<TakeFront<Type<int, char, long>, 3>, Type<int, char, long>>);
  static_assert(Same<TakeFront<Type<int, char, long>, 2>, Type<int, char>>);
  static_assert(Same<TakeFront<Type<int, char, long>, 1>, Type<int>>);
  static_assert(Same<TakeFront<Type<int, char, long>, 0>, EmptyType>);
  static_assert(Same<TakeFront<EmptyType, 0>, EmptyType>);
  static_assert(Same<TakeFront<EmptyType, 1>, EmptyType>);
  
  // Splice
  
  /// Take a sublist of types given a position and size
  template <typename List, size_t Pos, size_t Size>
  using Splice = TakeFront<PopFront<List, Pos>, Size>;
  
  static_assert(Same<Splice<Type<char, short, int, long, long long>, 1, 3>, Type<short, int, long>>);
  
  // Repeat
  
  /// Create a list by repeating a type
  template <typename Type, size_t Size>
  using Repeat = PushFront<EmptyType, Type, Size>;
  
  static_assert(Same<Repeat<int, 3>, Type<int, int, int>>);
  static_assert(Same<Repeat<int, 0>, EmptyType>);
  
  // Push Back
  
  /// Push one or more copies of a type onto the back of the list
  template <typename List, typename Type, size_t Num = 1>
  using PushBack = Concat<List, Repeat<Type, Num>>;
  
  static_assert(Same<PushBack<Type<int, char>, long, 2>, Type<int, char, long, long>>);
  
  // Pop Back
  
  /// Pop one or more types from the back of the list
  template <typename List, size_t Num = 1>
  using PopBack = TakeFront<List, Size<List> - Num>;
  
  static_assert(Same<PopBack<Type<int, char, long>>, Type<int, char>>);
  static_assert(Same<PopBack<EmptyType>, EmptyType>);
  
  // Take Back
  
  /// Take a list of types from the back of the list
  template <typename List, size_t S>
  using TakeBack = PopFront<List, Size<List> - S>;
  
  static_assert(Same<TakeBack<Type<int, char, long, float>, 2>, Type<long, float>>);
  
  // Insert
  
  /// Insert a list at an index of another list
  template <typename List, size_t Pos, typename InsertedList>
  using Insert = Concat<TakeFront<List, Pos>, InsertedList, PopFront<List, Pos>>;
  
  static_assert(Same<Insert<EmptyType, 0, EmptyType>, EmptyType>);
  static_assert(Same<Insert<EmptyType, 1, EmptyType>, EmptyType>);
  static_assert(Same<Insert<EmptyType, 2, Type<int, char>>, Type<int, char>>);
  static_assert(Same<Insert<Type<int, char, long>, 1, EmptyType>, Type<int, char, long>>);
  static_assert(Same<Insert<Type<char, long>, 0, Type<int, float>>, Type<int, float, char, long>>);
  static_assert(Same<Insert<Type<int, long>, 1, Type<char, float>>, Type<int, char, float, long>>);
  static_assert(Same<Insert<Type<int, char>, 2, Type<long, float>>, Type<int, char, long, float>>);
  
  // Insert One
  
  /// Insert a single type an an index of a list
  template <typename List, size_t Pos, typename T>
  using InsertOne = Insert<List, Pos, Type<T>>;
  
  static_assert(Same<InsertOne<Type<char, long>, 0, int>, Type<int, char, long>>);
  static_assert(Same<InsertOne<Type<int, long>, 1, char>, Type<int, char, long>>);
  static_assert(Same<InsertOne<Type<int, char>, 2, long>, Type<int, char, long>>);
  
  // Erase
  
  /// Erase types from the list
  template <typename List, size_t Pos, size_t Size = 1>
  using Erase = Concat<TakeFront<List, Pos>, PopFront<List, Pos + Size>>;
  
  static_assert(Same<Erase<Type<int, char, long>, 0, 0>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<int, char, long>, 1, 0>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<int, char, long>, 2, 0>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<int, char, long>, 3, 0>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<float, double, int, char, long>, 0, 2>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<int, float, double, char, long>, 1, 2>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<int, char, float, double, long>, 2, 2>, Type<int, char, long>>);
  static_assert(Same<Erase<Type<int, char, long, float, double>, 3, 2>, Type<int, char, long>>);
  
  // Remove
  
  namespace detail {
    template <typename List, typename Type>
    struct RemoveI;
    
    template <typename T, typename First, typename... Types>
    struct RemoveI<Type<First, Types...>, T> {
      using type = Concat<Type<First>, typename RemoveI<Type<Types...>, T>::type>;
    };
    
    template <typename First, typename... Types>
    struct RemoveI<Type<First, Types...>, First> {
      using type = typename RemoveI<Type<Types...>, First>::type;
    };
    
    template <typename T>
    struct RemoveI<EmptyType, T> {
      using type = EmptyType;
    };
  }
  
  /// Remove a type from a list
  template <typename List, typename Type>
  using Remove = typename detail::RemoveI<List, Type>::type;
  
  static_assert(Same<Remove<Type<int, char, long>, float>, Type<int, char, long>>);
  static_assert(Same<Remove<Type<int, char, long>, int>, Type<char, long>>);
  static_assert(Same<Remove<Type<int, char, long>, char>, Type<int, long>>);
  static_assert(Same<Remove<Type<int, char, long>, long>, Type<int, char>>);
  static_assert(Same<Remove<Type<float, int, float, char, float, long>, float>, Type<int, char, long>>);
}

#endif
