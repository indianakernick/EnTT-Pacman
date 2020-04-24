//
//  rand.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 14/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_rand_hpp
#define engine_math_rand_hpp

#include <random>
#include <iterator>

namespace Math {
  template <typename Gen, typename BeginIter, typename EndIter>
  size_t weightedRand(Gen &gen, const BeginIter begin, const EndIter end) {
    using Prob = typename std::iterator_traits<BeginIter>::value_type;
    
    size_t size = 0;
    Prob sum{0};
    for (BeginIter w = begin; w != end; ++w) {
      sum += *w;
      ++size;
    }
    
    std::uniform_int_distribution<Prob> dist(Prob{0}, sum);
    Prob choice = dist(gen);
    BeginIter w = begin;
    
    for (size_t i = 0; i != size; ++i, ++w) {
      const Prob weight = *w;
      if (choice <= weight) {
        return i;
      }
      choice -= weight;
    }
    
    assert(false);
    return -size_t(1);
  }
}

#endif
