//
//  write surface.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <string>
#include "../Memory/alloc.hpp"
#include "../Memory/file io.hpp"

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_MALLOC(SIZE) Memory::alloc(SIZE)
#define STBIW_REALLOC_SIZED(PTR, OLD_SIZE, NEW_SIZE) Memory::realloc(PTR, OLD_SIZE, NEW_SIZE)
#define STBIW_FREE(PTR) Memory::dealloc(PTR)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomma"
#pragma clang diagnostic ignored "-Wunused-function"

#include "stb_image_write.h"

#pragma clang diagnostic pop

inline G2D::SurfaceWriteError::SurfaceWriteError(const std::string_view file)
  : std::runtime_error(
      std::string("Failed to write surface to file \"")
      + std::string(file)
      + '\"'
    ) {}

namespace G2D::detail {
  inline void writeFunc(void *context, void *data, int size) {
    std::FILE *file = reinterpret_cast<std::FILE *>(context);
    Memory::writeFile(data, size, file);
  }
}

inline void G2D::writeSurface(const std::string_view path, const Surface &surface) {
  Memory::FileHandle file = Memory::openFileWrite(path);
  const int success = stbi_write_png_to_func(
    detail::writeFunc,
    file.get(),
    static_cast<int>(surface.width()),
    static_cast<int>(surface.height()),
    static_cast<int>(surface.bytesPerPixel()),
    surface.data(),
    static_cast<int>(surface.pitch())
  );
  
  if (success == 0) {
    throw SurfaceWriteError(path);
  }
}
