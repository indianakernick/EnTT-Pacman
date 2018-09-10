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
  template <typename Generator, typename BeginIterator, typename EndIterator>
  size_t weightedRand(const BeginIterator begin, const EndIterator end) {
    using Traits = std::iterator_traits<BeginIterator>;
    using Num = typename Traits::value_type;
    
    size_t size = 0;
    Num sum(0);
    for (BeginIterator w = begin; w != end; ++w) {
      sum += *w;
      ++size;
    }
    
    std::uniform_int_distribution<Num> dist(Num(0), sum);
    Generator gen;
    Num choice = dist(gen);
    BeginIterator w = begin;
    
    for (size_t i = 0; i != size; ++i, ++w) {
      const Num weight = *w;
      if (choice < weight) {
        return i;
      }
      choice -= weight;
    }
    
    assert(false);
    return -size_t(1);
  }
}

#endif
