//
//  round.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 10/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_round_hpp
#define engine_math_round_hpp

#include "pow.hpp"
#include "../Utils/bits.hpp"

namespace Math {
  ///Ceil num to the nearest power of 2
  constexpr unsigned long long ceilToPowerOf2(const unsigned long long num) {
    assert(num != 0);
    
    return (1 << (Utils::bits<long long> - __builtin_clzll(num - 1))) - (num == 1);
  }
  
  ///Ceil num to the nearest power of 2
  constexpr unsigned long ceilToPowerOf2(const unsigned long num) {
    assert(num != 0);
    
    return (1 << (Utils::bits<long> - __builtin_clzl(num - 1))) - (num == 1);
  }
  
  ///Ceil num to the nearest power of 2
  constexpr unsigned ceilToPowerOf2(const unsigned num) {
    assert(num != 0);
    
    return (1 << (Utils::bits<int> - __builtin_clz(num - 1))) - (num == 1);
  }
  
  ///Ceil num to the nearest power of 2
  constexpr unsigned short ceilToPowerOf2(const unsigned short num) {
    return ceilToPowerOf2(static_cast<unsigned>(num));
  }
  
  ///Ceil num to the nearest power of 2
  constexpr unsigned char ceilToPowerOf2(const unsigned char num) {
    return ceilToPowerOf2(static_cast<unsigned>(num));
  }
  
  ///Floor num to the nearest power of 2
  constexpr unsigned long long floorToPowerOf2(const unsigned long long num) {
    assert(num != 0);
    
    return (1 << ((Utils::bits<long long> - 1) - __builtin_clzll(num)));
  }
  
  ///Floor num to the nearest power of 2
  constexpr unsigned long floorToPowerOf2(const unsigned long num) {
    assert(num != 0);
    
    return (1 << ((Utils::bits<long> - 1) - __builtin_clzl(num)));
  }
  
  ///Floor num to the nearest power of 2
  constexpr unsigned floorToPowerOf2(const unsigned num) {
    assert(num != 0);
    
    return (1 << ((Utils::bits<int> - 1) - __builtin_clz(num)));
  }
  
  ///Floor num to the nearest power of 2
  constexpr unsigned short floorToPowerOf2(const unsigned short num) {
    return floorToPowerOf2(static_cast<unsigned>(num));
  }
  
  ///Floor num to the nearest power of 2
  constexpr unsigned char floorToPowerOf2(const unsigned char num) {
    return floorToPowerOf2(static_cast<unsigned>(num));
  }
  
  #define SIGNED_CEIL_FLOOR(POS_FUN, NEG_FUN, FUN)                              \
  template <typename SignedInt>                                                 \
  constexpr std::enable_if_t<                                                   \
    std::is_signed<SignedInt>::value,                                           \
    SignedInt                                                                   \
  >                                                                             \
  POS_FUN##FUN(const SignedInt num) {                                           \
    if (num < SignedInt(0)) {                                                   \
      return -NEG_FUN##FUN(static_cast<std::make_unsigned_t<SignedInt>>(-num)); \
    } else {                                                                    \
      return POS_FUN##FUN(static_cast<std::make_unsigned_t<SignedInt>>(num));   \
    }                                                                           \
  }
  
  ///Ceil num to the nearest power of 2
  SIGNED_CEIL_FLOOR(ceil, floor, ToPowerOf2)
  ///Floor num to the nearest power of 2
  SIGNED_CEIL_FLOOR(floor, ceil, ToPowerOf2)
  
  ///Ceil num to the nearest power of base
  template <typename UnsignedInt>
  constexpr std::enable_if_t<
    std::is_unsigned<UnsignedInt>::value,
    UnsignedInt
  >
  ceilToPower(const UnsignedInt base, const UnsignedInt num) {
    return pow(base, logCeil(base, num));
  }
  
  ///Floor num to the nearest power of base
  template <typename UnsignedInt>
  constexpr std::enable_if_t<
    std::is_unsigned<UnsignedInt>::value,
    UnsignedInt
  >
  floorToPower(const UnsignedInt base, const UnsignedInt num) {
    return pow(base, log(base, num));
  }
  
  ///Ceil num to the nearest power of base
  SIGNED_CEIL_FLOOR(ceil, floor, ToPower)
  ///Floor num to the nearest power of base
  SIGNED_CEIL_FLOOR(floor, ceil, ToPower)
  
  ///Ceil num to the nearest multiple of 2
  template <typename UnsignedInt>
  constexpr std::enable_if_t<
    std::is_unsigned<UnsignedInt>::value,
    UnsignedInt
  >
  ceilToEven(const UnsignedInt num) {
    return (num + UnsignedInt(1)) & ~UnsignedInt(1);
  }
  
  ///Floor num to the nearest multiple of 2
  template <typename UnsignedInt>
  constexpr std::enable_if_t<
    std::is_unsigned<UnsignedInt>::value,
    UnsignedInt
  >
  floorToEven(const UnsignedInt num) {
    return num & ~UnsignedInt(1);
  }
  
  ///Ceil num to the nearest multiple of 2
  SIGNED_CEIL_FLOOR(ceil, floor, ToEven)
  ///Floor num to the nearest multiple of 2
  SIGNED_CEIL_FLOOR(floor, ceil, ToEven)
  
  #undef SIGNED_CEIL_FLOOR
  
  ///Ceil num to the nearest multiple of factor
  template <typename UnsignedInt>
  constexpr std::enable_if_t<
    std::is_unsigned<UnsignedInt>::value,
    UnsignedInt
  >
  ceilToMultiple(const UnsignedInt factor, const UnsignedInt num) {
    assert(factor != UnsignedInt{0});
    return (num + factor - UnsignedInt{1}) / factor * factor;
  }
  
  ///Floor num to the nearest multiple of factor
  template <typename UnsignedInt>
  constexpr std::enable_if_t<
    std::is_unsigned<UnsignedInt>::value,
    UnsignedInt
  >
  floorToMultiple(const UnsignedInt factor, const UnsignedInt num) {
    assert(factor != UnsignedInt{0});
    return num / factor * factor;
  }
  
  ///Ceil num to the nearest multiple of factor
  template <typename SignedInt>
  constexpr std::enable_if_t<
    std::is_signed<SignedInt>::value,
    SignedInt
  >
  ceilToMultiple(const SignedInt factor, const SignedInt num) {
    using UnsignedInt = std::make_unsigned_t<SignedInt>;
    assert(factor > SignedInt{0});
    if (num < SignedInt(0)) {
      return -floorToMultiple(static_cast<UnsignedInt>(factor), static_cast<UnsignedInt>(-num));
    } else {
      return ceilToMultiple(static_cast<UnsignedInt>(factor), static_cast<UnsignedInt>(num));
    }
  }
  
  ///Floor num to the nearest multiple of factor
  template <typename SignedInt>
  constexpr std::enable_if_t<
    std::is_signed<SignedInt>::value,
    SignedInt
  >
  floorToMultiple(const SignedInt factor, const SignedInt num) {
    using UnsignedInt = std::make_unsigned_t<SignedInt>;
    assert(factor > SignedInt{0});
    if (num < SignedInt(0)) {
      return -ceilToMultiple(static_cast<UnsignedInt>(factor), static_cast<UnsignedInt>(-num));
    } else {
      return floorToMultiple(static_cast<UnsignedInt>(factor), static_cast<UnsignedInt>(num));
    }
  }
  
  ///Compute the ceil of the division of num and den
  template <typename Num, typename Den>
  constexpr std::enable_if_t<
    std::is_unsigned<Num>::value &&
    std::is_unsigned<Den>::value,
    std::common_type_t<Num, Den>
  >
  divCeil(const Num num, const Den den) {
    return (num + den - 1) / den;
  }
  
  ///Compute the ceil of the division of num and den
  template <typename Num, typename Den>
  constexpr std::enable_if_t<
    std::is_signed<Num>::value ||
    std::is_signed<Den>::value,
    std::common_type_t<Num, Den>
  >
  divCeil(const Num num, const Den den) {
    //http://stackoverflow.com/a/17005764
    return num / den + (((num < 0) ^ (den > 0)) && (num % den));
  }
  
  ///Compute the round of the division of num and den
  template <typename Num, typename Den>
  constexpr std::enable_if_t<
    std::is_unsigned<Num>::value &&
    std::is_unsigned<Den>::value,
    std::common_type_t<Num, Den>
  >
  divRound(const Num num, const Den den) {
    return (num + den / 2) / den;
  }
  
  ///Compute the round of the division of num and den
  template <typename Num, typename Den>
  constexpr std::enable_if_t<
    std::is_signed<Num>::value ||
    std::is_signed<Den>::value,
    std::common_type_t<Num, Den>
  >
  divRound(const Num num, const Den den) {
    //http://stackoverflow.com/a/18067292
    return ((num < 0) ^ (den < 0)) ? ((num - den / 2) / den)
                                   : ((num + den / 2) / den);
  }
}

#endif
