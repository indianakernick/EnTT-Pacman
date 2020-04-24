//
//  pos.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_pos_hpp
#define engine_grid_pos_hpp

#include <cstdint>
#include <glm/vec2.hpp>

namespace Grid {
  using Coord = int32_t;
  using Pos = glm::tvec2<Coord>;
}

#endif
