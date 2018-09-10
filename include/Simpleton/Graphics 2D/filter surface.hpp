//
//  filter surface.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_filter_surface_hpp
#define engine_graphics_2d_filter_surface_hpp

#include "surface.hpp"

namespace G2D {
  template <uint32_t BPP, typename Function>
  void filterInplace(G2D::Surface &, Function &&);
  
  template <uint32_t DST_BPP, uint32_t SRC_BPP, typename Function>
  void filterCopy(G2D::Surface &, const G2D::Surface &, Function &&);
}

#include "filter surface.inl"

#endif
