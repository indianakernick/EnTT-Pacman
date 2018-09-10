//
//  siconstants.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_siconstants_hpp
#define engine_math_siconstants_hpp

#include "pow.hpp"

#define GET_MACRO(_1, _2, NAME, ...) NAME
#define MATH_SI1(FROM) Math::SI::Conv<Math::SI::FROM>::value
#define MATH_SI2(FROM, TO) Math::SI::Conv<Math::SI::FROM, Math::SI::TO>::value
///A convenience macro. Shortens your lines
#define MATH_SI(...) GET_MACRO(__VA_ARGS__, MATH_SI2, MATH_SI1, filler)(__VA_ARGS__)

namespace Math {
  namespace SI {
    constexpr int YOCTO = -24;
    constexpr int ZEPTO = -21;
    constexpr int ATTO  = -18;
    constexpr int FEMTO = -15;
    constexpr int PICO  = -12;
    constexpr int NANO  = -9;
    constexpr int MICRO = -6;
    constexpr int MILLI = -3;
    constexpr int CENTI = -2;
    constexpr int DECI  = -1;
    constexpr int ONE   = 0;
    constexpr int DECA  = 1;
    constexpr int HECTO = 2;
    constexpr int KILO  = 3;
    constexpr int MEGA  = 6;
    constexpr int GIGA  = 9;
    constexpr int TERA  = 12;
    constexpr int PETA  = 15;
    constexpr int EXA   = 18;
    constexpr int ZETTA = 21;
    constexpr int YOTTA = 24;
    
    template <int FROM, int TO = ONE>
    struct Conv {
      static constexpr double value = pow(10.0, FROM - TO);
    };
  }
  
  namespace Literals {
    constexpr double operator""_yotta(long double value) {
      return value * MATH_SI(YOTTA);
    }
    constexpr double operator""_zetta(long double value) {
      return value * MATH_SI(ZETTA);
    }
    constexpr double operator""_exa(long double value) {
      return value * MATH_SI(EXA);
    }
    constexpr double operator""_peta(long double value) {
      return value * MATH_SI(PETA);
    }
    constexpr double operator""_tera(long double value) {
      return value * MATH_SI(TERA);
    }
    constexpr double operator""_giga(long double value) {
      return value * MATH_SI(GIGA);
    }
    constexpr double operator""_mega(long double value) {
      return value * MATH_SI(MEGA);
    }
    constexpr double operator""_kilo(long double value) {
      return value * MATH_SI(KILO);
    }
    constexpr double operator""_hecto(long double value) {
      return value * MATH_SI(HECTO);
    }
    constexpr double operator""_deca(long double value) {
      return value * MATH_SI(DECA);
    }
    constexpr double operator""_deci(long double value) {
      return value * MATH_SI(DECI);
    }
    constexpr double operator""_centi(long double value) {
      return value * MATH_SI(CENTI);
    }
    constexpr double operator""_milli(long double value) {
      return value * MATH_SI(MILLI);
    }
    constexpr double operator""_micro(long double value) {
      return value * MATH_SI(MICRO);
    }
    constexpr double operator""_nano(long double value) {
      return value * MATH_SI(NANO);
    }
    constexpr double operator""_pico(long double value) {
      return value * MATH_SI(PICO);
    }
    constexpr double operator""_femto(long double value) {
      return value * MATH_SI(FEMTO);
    }
    constexpr double operator""_atto(long double value) {
      return value * MATH_SI(ATTO);
    }
    constexpr double operator""_zepto(long double value) {
      return value * MATH_SI(ZEPTO);
    }
    constexpr double operator""_yocto(long double value) {
      return value * MATH_SI(YOCTO);
    }
  }
}

#endif
