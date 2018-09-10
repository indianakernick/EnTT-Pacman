//
//  pow.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_pow_hpp
#define engine_math_pow_hpp

#include <cassert>
#include <type_traits>
#include "../Utils/bits.hpp"

namespace Math {
  template <typename Number>
  constexpr Number square(const Number n) {
    return n * n;
  }
  
  template <typename Number>
  constexpr Number cube(const Number n) {
    return n * n * n;
  }

  //24% faster than std::pow for integers

  template <typename Number, typename Exponent>
  constexpr std::enable_if_t<std::is_unsigned_v<Exponent>, Number>
  pow(const Number num, Exponent exp) {
    Number out = Number(1);
    while (exp--) {
      out *= num;
    }
    return out;
  }
  
  template <typename Number, typename Exponent>
  constexpr std::enable_if_t<std::is_signed_v<Exponent>, Number>
  pow(const Number num, const Exponent exp) {
    if (exp < Exponent(0)) {
      return Number(1) / pow(num, static_cast<std::make_unsigned_t<Exponent>>(-exp));
    } else {
      return pow(num, static_cast<std::make_unsigned_t<Exponent>>(exp));
    }
  }
  
  template <long long EXPONENT, typename Number>
  constexpr Number pow(const Number num) {
    if constexpr (EXPONENT < 0ll) {
      assert(num != Number(0));
      return Number(1) / pow<-EXPONENT>(num);
    } else if constexpr (EXPONENT == 0ll) {
      return Number(1);
    } else if constexpr (EXPONENT == 1ll) {
      return num;
    } else if constexpr (EXPONENT == 2ll) {
      return num * num;
    } else {
      const Number half = pow<EXPONENT / 2ll>(num);
      return half * half * pow<EXPONENT % 2ll>(num);
    }
  }
  
  //1314% faster than std::log2
  
  ///Compute the floor of the base 2 logarithm of a number
  constexpr unsigned long long log2(const unsigned long long num) {
    assert(num != 0);
  
    return (Utils::bits<long long> - 1) - __builtin_clzll(num);
  }
  
  ///Compute the floor of the base 2 logarithm of a number
  constexpr unsigned long log2(const unsigned long num) {
    assert(num != 0);
  
    return (Utils::bits<long> - 1) - __builtin_clzl(num);
  }
  
  ///Compute the floor of the base 2 logarithm of a number
  constexpr unsigned log2(const unsigned num) {
    assert(num != 0);
  
    return (Utils::bits<int> - 1) - __builtin_clz(num);
  }
  
  ///Compute the floor of the base 2 logarithm of a number
  constexpr unsigned short log2(const unsigned short num) {
    return log2(static_cast<unsigned>(num));
  }
  
  ///Compute the floor of the base 2 logarithm of a number
  constexpr unsigned char log2(const unsigned char num) {
    return log2(static_cast<unsigned>(num));
  }
  
  //272.3% faster than std::ceil(std::log2)
  
  ///Compute the ceil of the base 2 logarithm of a number
  constexpr unsigned long long log2Ceil(const unsigned long long num) {
    assert(num != 0);
    
    const unsigned long long leading = __builtin_clzll(num);
    constexpr unsigned long long bits = Utils::bits<long long>;
    return bits - leading - (leading + __builtin_ctzll(num) == bits - 1);
  }
  
  ///Compute the ceil of the base 2 logarithm of a number
  constexpr unsigned long log2Ceil(const unsigned long num) {
    assert(num != 0);
    
    const unsigned long leading = __builtin_clzl(num);
    constexpr unsigned long bits = Utils::bits<long>;
    return bits - leading - (leading + __builtin_ctzl(num) == bits - 1);
  }
  
  ///Compute the ceil of the base 2 logarithm of a number
  constexpr unsigned log2Ceil(const unsigned num) {
    assert(num != 0);
    
    const unsigned leading = __builtin_clz(num);
    constexpr unsigned bits = Utils::bits<int>;
    return bits - leading - (leading + __builtin_ctz(num) == bits - 1);
  }
  
  ///Compute the ceil of the base 2 logarithm of a number
  constexpr unsigned short log2Ceil(const unsigned short num) {
    return log2Ceil(static_cast<unsigned>(num));
  }
  
  ///Compute the ceil of the base 2 logarithm of a number
  constexpr unsigned char log2Ceil(const unsigned char num) {
    return log2Ceil(static_cast<unsigned>(num));
  }
  
  ///Compute the floor of the logarithm of a number
  template <typename Number>
  constexpr Number log(const Number base, Number num) {
    assert(base > 1);
    assert(num > 0);
    
    Number count = 0;
    while (num /= base) {
      ++count;
    }
    return count;
  }
  
  ///Compute the ceil of the logarithm of a number
  template <typename Number>
  constexpr Number logCeil(const Number base, Number num) {
    assert(base > 1);
    assert(num > 0);
    
    Number count = 0;
    bool up = false;
    while (Number numDivBase = num / base) {
      up = up || (num % base);
      ++count;
      num = numDivBase;
    }
    return count + up;
  }
  
  ///Is num a power of 2?
  template <typename Number>
  constexpr bool isPowerOf2(const Number num) {
    assert(num > 0);
    
    return (num & (num - 1)) == 0;
  }
  
  ///Is num a power of base?
  template <typename Number>
  constexpr bool isPower(const Number base, Number num) {
    assert(base > 1);
    assert(num > 0);
    
    while (num % base == 0) {
      num /= base;
    }
    return num == 1;
  }
}

#endif
