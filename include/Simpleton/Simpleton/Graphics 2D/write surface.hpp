//
//  write surface.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_write_surface_hpp
#define engine_graphics_2d_write_surface_hpp

#include <stdexcept>
#include "surface.hpp"
#include <string_view>

namespace G2D {
  class SurfaceWriteError final : public std::runtime_error {
  public:
    explicit SurfaceWriteError(std::string_view);
  };

  void writeSurface(std::string_view, const Surface &);
}
  
#include "write surface.inl"

#endif
