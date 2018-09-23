//
//  alloc.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 16/8/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_alloc_hpp
#define engine_memory_alloc_hpp

#include <new>
#include <cstring>
#include <cstddef>

namespace Memory {
  /// Allocate memory
  inline void *alloc(const size_t bytes) {
    return operator new(
      bytes, std::align_val_t{alignof(std::max_align_t)}
    );
  }

  /// Allocate uninitialized bytes
  inline std::byte *allocBytes(const size_t bytes) {
    return static_cast<std::byte *>(alloc(bytes));
  }
  
  /// Allocate uninitialized object
  template <typename Object>
  Object *allocObj() {
    return static_cast<Object *>(operator new(
      sizeof(Object), std::align_val_t{alignof(Object)}
    ));
  }
  
  /// Allocate uninitialized array of objects
  template <typename Object>
  Object *allocArr(const size_t count) {
    return static_cast<Object *>(operator new(
      sizeof(Object) * count, std::align_val_t{alignof(Object)}
    ));
  }

  /// Deallocate memory
  inline void dealloc(void *const ptr) {
    operator delete(ptr);
  }
  
  /// Reallocate memory
  inline void *realloc(void *const ptr, const size_t oldSize, const size_t newSize) {
    void *const newPtr = alloc(newSize);
    std::memcpy(newPtr, ptr, oldSize < newSize ? oldSize : newSize);
    dealloc(ptr);
    return newPtr;
  }
}

#endif
