//
//  blit surface.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_blit_surface_hpp
#define engine_graphics_2d_blit_surface_hpp

#include <stdexcept>
#include "surface.hpp"

namespace G2D {
  class FormatError final : public std::exception {
  public:
    FormatError() = default;
    
    const char *what() const noexcept override;
  };

  void blit(Surface &, const Surface &);
  void blit(Surface &, const Surface &, Surface::Size, Surface::Size);
}
  
#include "blit surface.inl"

#endif
