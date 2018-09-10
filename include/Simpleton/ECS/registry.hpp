//
//  registry.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_registry_hpp
#define engine_ecs_registry_hpp

#include <entt/entity/registry.hpp>

namespace ECS {
  using Registry = entt::DefaultRegistry;
  using EntityID = Registry::entity_type;
}

#endif
