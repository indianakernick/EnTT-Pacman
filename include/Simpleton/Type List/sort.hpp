//
//  sort.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_sort_hpp
#define engine_type_list_sort_hpp

#include "splice.hpp"
#include "../Utils/type name.hpp"

namespace List {
  // Left Half
  
  /// The left half of a list. Left is smaller than right when size is odd
  template <typename List>
  using LeftHalf = Splice<List, 0, Size<List> / 2>;
  
  static_assert(Same<LeftHalf<Type<int, char, long>>, Type<int>>);
  
  // Right Half
  
  /// The right half of a list. Left is smaller than right when size is odd
  template <typename List>
  using RightHalf = Splice<List, Size<List> / 2, (Size<List> + 1) / 2>;
  
  static_assert(Same<RightHalf<Type<int, char, long>>, Type<char, long>>);

  // Merge
  
  namespace detail {
    template <bool Cond, typename True, typename False>
    struct ConditionalHelper;
    
    template <typename True, typename False>
    struct ConditionalHelper<true, True, False> {
      using type = True;
    };
    
    template <typename True, typename False>
    struct ConditionalHelper<false, True, False> {
      using type = False;
    };
    
    template <bool Cond, typename True, typename False>
    using Conditional = typename ConditionalHelper<Cond, True, False>::type;
  
    template <typename LeftList, typename RightList, template <typename, typename> typename Less>
    struct MergeI;
    
    template <
      template <typename, typename> typename Less,
      typename LeftFirst,
      typename RightFirst,
      typename... LeftTypes,
      typename... RightTypes
    >
    struct MergeI<Type<LeftFirst, LeftTypes...>, Type<RightFirst, RightTypes...>, Less> {
      using type = Conditional<
        Less<LeftFirst, RightFirst>::value,
        Concat<Type<LeftFirst>, typename MergeI<Type<LeftTypes...>, Type<RightFirst, RightTypes...>, Less>::type>,
        Concat<Type<RightFirst>, typename MergeI<Type<LeftFirst, LeftTypes...>, Type<RightTypes...>, Less>::type>
      >;
    };
    
    template <typename LeftList, template <typename, typename> typename Less>
    struct MergeI<LeftList, EmptyType, Less> {
      using type = LeftList;
    };
    
    template <typename RightList, template <typename, typename> typename Less>
    struct MergeI<EmptyType, RightList, Less> {
      using type = RightList;
    };
    
    template <template <typename, typename> typename Less>
    struct MergeI<EmptyType, EmptyType, Less> {
      using type = EmptyType;
    };
    
    template <typename Left, typename Right>
    struct SizeLess {
      static constexpr bool value = sizeof(Left) < sizeof(Right);
    };
    
    template <typename Left, typename Right>
    struct NameLess {
      static constexpr bool value = Utils::typeLess<Left, Right>();
    };
    
    static_assert(Same<
      typename MergeI<Type<char[4]>, Type<char[2], char[8]>, SizeLess>::type,
      Type<char[2], char[4], char[8]>
    >);
  }
  
  // Sort
  
  namespace detail {
    template <typename List, template <typename, typename> typename Less>
    struct SortI {
      using type = typename MergeI<
        typename SortI<LeftHalf<List>, Less>::type,
        typename SortI<RightHalf<List>, Less>::type,
        Less
      >::type;
    };
    
    template <typename First, typename Second, template <typename, typename> typename Less>
    struct SortI<Type<First, Second>, Less> {
      using type = Conditional<
        Less<First, Second>::value,
        Type<First, Second>,
        Type<Second, First>
      >;
    };
    
    template <typename T, template <typename, typename> typename Less>
    struct SortI<Type<T>, Less> {
      using type = Type<T>;
    };
    
    template <template <typename, typename> typename Less>
    struct SortI<EmptyType, Less> {
      using type = EmptyType;
    };
  }
  
  /// Sort the list by a predicate. Predicate must be a struct that takes two
  /// types and has a value member
  template <typename List, template <typename, typename> typename Less>
  using Sort = typename detail::SortI<List, Less>::type;
  
  static_assert(Same<
    Sort<Type<char[8], char[4], char[2]>, detail::SizeLess>,
    Type<char[2], char[4], char[8]>
  >);
  static_assert(Same<Sort<EmptyType, detail::SizeLess>, EmptyType>);
  
  // Is permutation of
  
  /// Is the first list a permutation of the second list?
  template <typename First, typename Second>
  constexpr bool IsPermut = Same<Sort<First, detail::NameLess>, Sort<Second, detail::NameLess>>;
  
  static_assert(IsPermut<Type<int>, Type<int>>);
  static_assert(IsPermut<Type<int, char, long>, Type<char, int, long>>);
  static_assert(IsPermut<EmptyType, EmptyType>);
  static_assert(!IsPermut<Type<int, char, long>, Type<char, int, int>>);
  
  // Is sorted
  
  /// Is the list sorted by the given predicate?
  template <typename List, template <typename, typename> typename Less>
  constexpr bool IsSorted = Same<List, Sort<List, Less>>;
  
  static_assert(IsSorted<EmptyType, detail::SizeLess>);
  static_assert(IsSorted<Type<char[2], char[3], char[4]>, detail::SizeLess>);
  static_assert(!IsSorted<Type<char[4], char[3], char[2]>, detail::SizeLess>);
}

#endif
