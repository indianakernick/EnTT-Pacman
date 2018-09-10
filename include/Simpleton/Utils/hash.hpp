//
//  hash.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 6/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_hash_hpp
#define engine_utils_hash_hpp

#include <array>
#include "tuple.hpp"
#include <functional>
#include "combine hashes.hpp"

namespace Utils {
  template <typename T>
  void hashCombine(size_t &seed, const T &value) {
    seed = combineHashes(seed, std::hash<T>()(value));
  }
}

template <typename T0, typename T1>
struct std::hash<std::pair<T0, T1>> {
  size_t operator()(const std::pair<T0, T1> &pair) const noexcept {
    size_t hash = 0;
    Utils::hashCombine(hash, pair.first);
    Utils::hashCombine(hash, pair.second);
    return hash;
  }
};

template <typename ...Ts>
struct std::hash<std::tuple<Ts...>> {
  size_t operator()(const std::tuple<Ts...> &tuple) const noexcept {
    size_t hash = 0;
    Utils::forEach(tuple, [&hash] (const auto value) {
      Utils::hashCombine(hash, value);
    });
    return hash;
  }
};

template <typename T, size_t SIZE>
struct std::hash<std::array<T, SIZE>> {
  size_t operator()(const std::array<T, SIZE> &array) const noexcept {
    size_t hash = 0;
    for (auto i = array.cbegin(); i != array.cend(); ++i) {
      Utils::hashCombine(hash, *i);
    }
    return hash;
  }
};

#endif
