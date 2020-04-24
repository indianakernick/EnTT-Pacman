//
//  int least.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_int_least_hpp
#define engine_utils_int_least_hpp

#include <cstdint>
#include "../Math/round.hpp"

namespace Utils {
  template <size_t BYTES>
  struct int_least {
    using type = typename int_least<Math::ceilToPowerOf2(BYTES)>::type;
  };

  ///Returns a signed integral type of at least the number of bytes specified
  template <size_t BYTES>
  using int_least_t = typename int_least<BYTES>::type;

  ///Returns an unsigned integral type of at least the number of bytes specified
  template <size_t BYTES>
  using uint_least_t = std::make_unsigned_t<int_least_t<BYTES>>;

  template <size_t BYTES>
  struct int_exact {};
  
  ///Returns a signed integral type of exactly the number of bytes specified
  template <size_t BYTES>
  using int_exact_t = typename int_exact<BYTES>::type;
  
  ///Returns an unsigned integral type of exactly the number of bytes specified
  template <size_t BYTES>
  using uint_exact_t = std::make_unsigned_t<int_exact_t<BYTES>>;

  #define SPECIALIZE(size, name)                                                \
  template <>                                                                   \
  struct int_least<size> {                                                      \
    using type = name;                                                          \
  };                                                                            \
                                                                                \
  template <>                                                                   \
  struct int_exact<size> {                                                      \
    using type = name;                                                          \
  }

  #if defined(UINT8_MAX) && UINT8_MAX == 255 //2^8-1
  SPECIALIZE(1, int8_t);
  #endif
  #if defined(UINT16_MAX) && UINT16_MAX == 65535 //2^16-1
  SPECIALIZE(2, int16_t);
  #endif
  #if defined(UINT32_MAX) && UINT32_MAX == 4294967295U //2^32-1
  SPECIALIZE(4, int32_t);
  #endif
  #if defined(UINT64_MAX) && UINT64_MAX == 18446744073709551615ULL //2^64-1
  SPECIALIZE(8, int64_t);
  #endif

  #if defined(__SIZEOF_INT128__) && __SIZEOF_INT128__ > 8
  SPECIALIZE(__SIZEOF_INT128__, __int128);
  #endif

  #undef SPECIALIZE

  ///Returns a signed integral type large enough to fit the specified types within it
  template <typename ...Types>
  using int_fit_t = int_least_t<(sizeof(Types) + ...)>;

  ///Returns an unsigned integral type large enough to fit the specified types within it
  template <typename ...Types>
  using uint_fit_t = uint_least_t<(sizeof(Types) + ...)>;
  
  ///Returns a floating point type of at least the number of bytes specified
  template <size_t BYTES>
  struct float_least {
    using type = typename float_least<Math::ceilToPowerOf2(BYTES)>::type;
  };
  
  template <size_t BYTES>
  struct float_exact {};
  
  ///Returns a floating point type of at least the number of bytes specified
  template <size_t BYTES>
  using float_least_t = typename float_least<BYTES>::type;
  
  ///Returns a floating point type of exactly the number of bytes specified
  template <size_t BYTES>
  using float_exact_t = typename float_exact<BYTES>::type;
  
  #define SPECIALIZE(size, name)                                                \
  template <>                                                                   \
  struct float_least<size> {                                                    \
    using type = name;                                                          \
  };                                                                            \
                                                                                \
  template <>                                                                   \
  struct float_exact<size> {                                                    \
    using type = name;                                                          \
  }
  
  SPECIALIZE(sizeof(float), float);
  #if __SIZEOF_FLOAT__ < __SIZEOF_DOUBLE__
  SPECIALIZE(sizeof(double), double);
  #endif
  #if __SIZEOF_DOUBLE__ < __SIZEOF_LONG_DOUBLE__
  SPECIALIZE(sizeof(long double), long double);
  #endif
  
  #undef SPECIALIZE
}

#endif
