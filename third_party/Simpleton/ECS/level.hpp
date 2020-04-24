//
//  level.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_level_hpp
#define engine_ecs_level_hpp

#include <limits>

namespace ECS {
  using Level = unsigned;
  
  constexpr Level NULL_LEVEL = std::numeric_limits<Level>::max();
  constexpr Level FINAL_LEVEL = NULL_LEVEL - 1;
}

#endif
