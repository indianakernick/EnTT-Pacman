//
//  combine hashes.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_combine_hashes_hpp
#define engine_utils_combine_hashes_hpp

#include <cstddef>

namespace Utils {
  constexpr size_t combineHashes(const size_t left, const size_t right) {
    //https://stackoverflow.com/a/8980550
    
    if constexpr (sizeof(size_t) == 8) {
      // CityHash
      const size_t mul = 0x9E3779B97F4A7C15ull;
      size_t a = (right ^ left) * mul;
      a ^= (a >> 47);
      size_t b = (left ^ a) * mul;
      b ^= (b >> 47);
      return b * mul;
    } else if constexpr (sizeof(size_t) == 4) {
      // boost hash_combine
      return left ^ (right + 0x9E3779B9 + (left << 6) + (left >> 2));
    }
  }
}

#endif
