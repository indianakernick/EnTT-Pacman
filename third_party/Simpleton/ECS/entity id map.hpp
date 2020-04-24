//
//  entity id map.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_entity_id_map_hpp
#define engine_ecs_entity_id_map_hpp

#include <vector>
#include <entt/entity/registry.hpp>

// @TODO Move this back to the one project that uses it
// I don't even know what this is for!
namespace ECS {
  using ClientEntityID = int;
  constexpr ClientEntityID NULL_CLIENT_ENTITY_ID = std::numeric_limits<ClientEntityID>::min();

  class EntityIDmap {
  public:
    EntityIDmap() = default;
    
    void insertPair(ClientEntityID, entt::entity);
    void insertNullPair(entt::entity);
    entt::entity getEntityFromID(ClientEntityID) const;
    entt::entity getEntityFromIndex(size_t) const;

  private:
    std::vector<std::pair<ClientEntityID, entt::entity>> map;
  };
}

#include "entity id map.inl"

#endif
