//
//  byteconstants.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_byteconstants_hpp
#define engine_math_byteconstants_hpp

#include <cstdint>

namespace Math {
  namespace Byte {
    constexpr uint64_t ONE  = 1ull;
    constexpr uint64_t KILO = 1ull << 10;
    constexpr uint64_t MEGA = 1ull << 20;
    constexpr uint64_t GIGA = 1ull << 30;
    constexpr uint64_t TERA = 1ull << 40;
    constexpr uint64_t PETA = 1ull << 50;
    constexpr uint64_t EXA  = 1ull << 60;
    
    constexpr uint64_t KILO_ONE  = KILO;
    
    constexpr uint64_t MEGA_ONE  = MEGA;
    constexpr uint64_t MEGA_KILO = KILO;
    
    constexpr uint64_t GIGA_ONE  = GIGA;
    constexpr uint64_t GIGA_KILO = MEGA;
    constexpr uint64_t GIGA_MEGA = KILO;
    
    constexpr uint64_t TERA_ONE  = TERA;
    constexpr uint64_t TERA_KILO = GIGA;
    constexpr uint64_t TERA_MEGA = MEGA;
    constexpr uint64_t TERA_GIGA = KILO;
    
    constexpr uint64_t PETA_ONE  = PETA;
    constexpr uint64_t PETA_KILO = TERA;
    constexpr uint64_t PETA_MEGA = GIGA;
    constexpr uint64_t PETA_GIGA = MEGA;
    constexpr uint64_t PETA_TERA = KILO;
    
    constexpr uint64_t EXA_ONE   = EXA;
    constexpr uint64_t EXA_KILO  = PETA;
    constexpr uint64_t EXA_MEGA  = TERA;
    constexpr uint64_t EXA_GIGA  = GIGA;
    constexpr uint64_t EXA_TERA  = MEGA;
    constexpr uint64_t EXA_PETA  = KILO;
  }
  
  namespace Literals {
    constexpr uint64_t operator""_b(uint64_t value) {
      return value * Math::Byte::ONE;
    }
    constexpr uint64_t operator""_kb(uint64_t value) {
      return value * Math::Byte::KILO;
    }
    constexpr uint64_t operator""_mb(uint64_t value) {
      return value * Math::Byte::MEGA;
    }
    constexpr uint64_t operator""_gb(uint64_t value) {
      return value * Math::Byte::GIGA;
    }
    constexpr uint64_t operator""_tb(uint64_t value) {
      return value * Math::Byte::TERA;
    }
    constexpr uint64_t operator""_pb(uint64_t value) {
      return value * Math::Byte::PETA;
    }
    constexpr uint64_t operator""_eb(uint64_t value) {
      return value * Math::Byte::EXA;
    }

    constexpr uint64_t operator""_b(long double value) {
      return value * Math::Byte::ONE;
    }
    constexpr uint64_t operator""_kb(long double value) {
      return value * Math::Byte::KILO;
    }
    constexpr uint64_t operator""_mb(long double value) {
      return value * Math::Byte::MEGA;
    }
    constexpr uint64_t operator""_gb(long double value) {
      return value * Math::Byte::GIGA;
    }
    constexpr uint64_t operator""_tb(long double value) {
      return value * Math::Byte::TERA;
    }
    constexpr uint64_t operator""_pb(long double value) {
      return value * Math::Byte::PETA;
    }
    constexpr uint64_t operator""_eb(long double value) {
      return value * Math::Byte::EXA;
    }
  }
}

#endif
