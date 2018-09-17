//
//  json.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_json_hpp
#define engine_ecs_json_hpp

#include "../Data/json.hpp"
#include "entity id map.hpp"

namespace ECS {
  void insertPairs(EntityIDmap &, const json &, Registry &);
}

#include "json.inl"

#endif
