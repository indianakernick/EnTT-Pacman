//
//  load surface.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_load_surface_hpp
#define engine_graphics_2d_load_surface_hpp

#include <stdexcept>
#include <string_view>
#include "surface.hpp"

namespace G2D {
  class SurfaceLoadError final : public std::runtime_error {
  public:
    SurfaceLoadError(std::string_view, std::string_view);
  };

  ///Load a surface with the same bytesPerPixel as the file
  Surface loadSurface(std::string_view);
  ///Load a surface with the specified bytesPerPixel
  Surface loadSurface(std::string_view, int);
  ///Load a surface with a bytesPerPixel of 3
  Surface loadSurfaceRGB(std::string_view);
  ///Load a surface with a bytesPerPixel of 4
  Surface loadSurfaceRGBA(std::string_view);
}

#include "load surface.inl"

#endif
