//
//  load surface.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <string>
#include "../Memory/alloc.hpp"
#include "../Memory/file io.hpp"

#define STBI_NO_GIF
#define STB_IMAGE_STATIC
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(SIZE) Memory::alloc(SIZE)
#define STBI_REALLOC_SIZED(PTR, OLD_SIZE, NEW_SIZE) Memory::realloc(PTR, OLD_SIZE, NEW_SIZE)
#define STBI_FREE(PTR) Memory::dealloc(PTR)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomma"
#pragma clang diagnostic ignored "-Wunused-function"

#include "stb_image.h"

#pragma clang diagnostic pop

inline G2D::SurfaceLoadError::SurfaceLoadError(
  const std::string_view file,
  const std::string_view reason
) : std::runtime_error(
      std::string("Failed to load surface: \"")
      + std::string(file)
      + "\": "
      + std::string(reason)
    ) {}

inline G2D::Surface G2D::loadSurface(const std::string_view path, const int bpp) {
  Memory::FileHandle file = Memory::openFileRead(path);
  int width, height;
  uint8_t *const data = stbi_load_from_file(file.get(), &width, &height, nullptr, bpp);
  if (data == nullptr) {
    throw SurfaceLoadError(path, stbi_failure_reason());
  }
  return Surface(width, height, bpp, width * bpp, data);
}

inline G2D::Surface G2D::loadSurface(const std::string_view path) {
  Memory::FileHandle file = Memory::openFileRead(path);
  int width, height, bytesPerPixel;
  uint8_t *const data = stbi_load_from_file(file.get(), &width, &height, &bytesPerPixel, 0);
  if (data == nullptr) {
    throw SurfaceLoadError(path, stbi_failure_reason());
  }
  return Surface(width, height, bytesPerPixel, width * bytesPerPixel, data);
}

inline G2D::Surface G2D::loadSurfaceRGB(const std::string_view path) {
  return loadSurface(path, STBI_rgb);
}

inline G2D::Surface G2D::loadSurfaceRGBA(const std::string_view path) {
  return loadSurface(path, STBI_rgb_alpha);
}
