//
//  endian.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 24/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_endian_hpp
#define engine_utils_endian_hpp

#include "int least.hpp"
#include <SDL2/SDL_endian.h>

namespace Utils {
  template <typename T>
  uint_exact_t<sizeof(T)> endianSwap(const T n) {
    if constexpr (sizeof(T) == 1) {
      return n;
    } else if constexpr (sizeof(T) == 2) {
      union {
        T t;
        uint16_t i;
      };
      t = n;
      return SDL_Swap16(i);
    } else if constexpr (sizeof(T) == 4) {
      union {
        T t;
        uint32_t i;
      };
      t = n;
      return SDL_Swap32(i);
    } else if constexpr (sizeof(T) == 8) {
      union {
        T t;
        uint64_t i;
      };
      t = n;
      return SDL_Swap64(i);
    }
  }
  
  template <typename T>
  void endianSwapCopy(T *dst, const T *src, const size_t size) {
    const T *const end = src + size;
    for (; src != end; ++src, ++dst) {
      const auto swapped = endianSwap(*src);
      std::memcpy(dst, &swapped, sizeof(T));
    }
  }
  
  template <typename T>
  uint_exact_t<sizeof(T)> toLilEndian(const T n) {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    return *reinterpret_cast<const uint_exact_t<sizeof(T)> *>(&n);
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
    return endianSwap(n);
#else
#error Unknown endianess
#endif
  }
  
  template <typename T>
  uint_exact_t<sizeof(T)> toBigEndian(const T n) {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    return endianSwap(n);
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
    return *reinterpret_cast<const uint_exact_t<sizeof(T)> *>(&n);
#else
#error Unknown endianess
#endif
  }
  
  template <typename T>
  uint_exact_t<sizeof(T)> fromLilEndian(const T n) {
    return toLilEndian(n);
  }
  
  template <typename T>
  uint_exact_t<sizeof(T)> fromBigEndian(const T n) {
    return toBigEndian(n);
  }
  
  template <typename T>
  void copyToLilEndian(void *const dst, const T *const src, const size_t size) {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    std::memcpy(dst, src, size * sizeof(T));
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
    endianSwapCopy(reinterpret_cast<T *>(dst), src, size);
#else
#error Unknown endianess
#endif
  }
  
  template <typename T>
  void copyToBigEndian(void *const dst, const T *const src, const size_t size) {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    endianSwapCopy(reinterpret_cast<T *>(dst), src, size);
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
    std::memcpy(dst, src, size * sizeof(T));
#else
#error Unknown endianess
#endif
  }
  
  template <typename T>
  void copyFromLilEndian(T *const dst, const void *const src, const size_t size) {
    copyToLilEndian(dst, reinterpret_cast<const T *>(src), size);
  }
  
  template <typename T>
  void copyFromBigEndian(T *const dst, const void *const src, const size_t size) {
    copyToBigEndian(dst, reinterpret_cast<const T *>(src), size);
  }
}

#endif
