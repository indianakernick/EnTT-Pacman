//
//  zsort.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 21/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_zsort_hpp
#define engine_graphics_2d_zsort_hpp

#include "geom types.hpp"

namespace G2D {
  /// Sort by the depth of the first vertex
  bool sort(const Quad &, const Quad &);
  /// Sort by the average depth of the verticies
  bool sortCenter(const Quad &, const Quad &);
  /// Sort by the depth of the deepest vertex
  bool sortDeep(const Quad &, const Quad &);
  /// Sort by the depth of the shallowest vertex
  bool sortShallow(const Quad &, const Quad &);
}

#include "zsort.inl"

#endif
