//
//  load prototype.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_load_prototype_hpp
#define engine_ecs_load_prototype_hpp

#include "../Data/json.hpp"
#include <entt/entity/prototype.hpp>

namespace ECS {
  /// Load an entt::prototype from a json object. Returns the number of keys that
  /// were unread
  template <typename CompList>
  int loadProto(entt::prototype &, const json &);
}

#include "load prototype.inl"

#endif
