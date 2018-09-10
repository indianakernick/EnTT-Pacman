//
//  realloc.hpp
//  Surface
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_realloc_hpp
#define engine_graphics_2d_realloc_hpp

#include <cstring>

namespace G2D::detail {
  inline void *reallocMem(void *const ptr, const size_t oldSize, const size_t newSize) {
    void *const newPtr = operator new(newSize);
    std::memcpy(newPtr, ptr, oldSize);
    operator delete(ptr);
    return newPtr;
  }
}

#endif
