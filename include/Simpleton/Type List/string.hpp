//
//  string.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/8/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_string_hpp
#define engine_type_list_string_hpp

#include "splice.hpp"

namespace List {
  template <char... Chars>
  struct Char {
    static constexpr const char chars[sizeof...(Chars) + 1] = {Chars..., '\0'};
    static constexpr size_t size = sizeof...(Chars);
  };
  
  namespace detail {
    template <char c>
    struct Character {};
    
    template <typename CharType>
    struct GetChars {};
    
    template <char... Chars>
    struct GetChars<Type<Character<Chars>...>> {
      using type = Char<Chars...>;
    };
    
    template <size_t Size, typename Str>
    struct TakeFrontCharsI {};
    
    template <size_t Size, char... Chars>
    struct TakeFrontCharsI<Size, Char<Chars...>> {
      static_assert(Size <= sizeof...(Chars), "String is too long");
      using type = typename GetChars<TakeFront<Type<Character<Chars>...>, Size>>::type;
    };
    
    template <size_t Size, typename Str>
    using TakeFrontChars = typename TakeFrontCharsI<Size, Str>::type;
  }
  
  #define LIST_DETAIL_GET_1(STR, I) ((I) < sizeof(STR) ? STR[I] : 0)
  
  #define LIST_DETAIL_GET_4(STR, I)                                             \
    LIST_DETAIL_GET_1(STR, I + 0) ,                                             \
    LIST_DETAIL_GET_1(STR, I + 1) ,                                             \
    LIST_DETAIL_GET_1(STR, I + 2) ,                                             \
    LIST_DETAIL_GET_1(STR, I + 3)
  #define LIST_DETAIL_GET_16(STR, I)                                            \
    LIST_DETAIL_GET_4(STR, I + 0) ,                                             \
    LIST_DETAIL_GET_4(STR, I + 4) ,                                             \
    LIST_DETAIL_GET_4(STR, I + 8) ,                                             \
    LIST_DETAIL_GET_4(STR, I + 12)
  #define LIST_DETAIL_GET_64(STR, I)                                            \
    LIST_DETAIL_GET_16(STR, I + 0) ,                                            \
    LIST_DETAIL_GET_16(STR, I + 16) ,                                           \
    LIST_DETAIL_GET_16(STR, I + 32) ,                                           \
    LIST_DETAIL_GET_16(STR, I + 48)
  #define LIST_DETAIL_GET_256(STR, I)                                           \
    LIST_DETAIL_GET_64(STR, I + 0) ,                                            \
    LIST_DETAIL_GET_64(STR, I + 64) ,                                           \
    LIST_DETAIL_GET_64(STR, I + 128) ,                                          \
    LIST_DETAIL_GET_64(STR, I + 192)
  
  #define LIST_CHAR(STRING_LITERAL)                                             \
    ::List::detail::TakeFrontChars<                                             \
      sizeof(STRING_LITERAL) - 1,                                               \
      ::List::Char<LIST_DETAIL_GET_256(STRING_LITERAL, 0)>                      \
    >
  
  static_assert(std::is_same_v<LIST_CHAR("foo"), LIST_CHAR("foo")>);
  static_assert(!std::is_same_v<LIST_CHAR("foo"), LIST_CHAR("bar")>);
}

#endif
