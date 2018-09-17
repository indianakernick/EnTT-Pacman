//
//  morton.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_morton_hpp
#define engine_grid_morton_hpp

#include "pos.hpp"

namespace Grid {
  using Morton = uint64_t;

  Morton toMorton(Pos);
  Pos fromMorton(Morton);
}

#include "morton.inl"

#endif
