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
#include "registry.hpp"

namespace ECS {
  using ClientEntityID = int;
  constexpr ClientEntityID NULL_CLIENT_ENTITY_ID = std::numeric_limits<ClientEntityID>::min();

  class EntityIDmap {
  public:
    EntityIDmap() = default;
    
    void insertPair(ClientEntityID, EntityID);
    void insertNullPair(EntityID);
    ECS::EntityID getEntityFromID(ClientEntityID) const;
    ECS::EntityID getEntityFromIndex(size_t) const;

  private:
    std::vector<std::pair<ClientEntityID, EntityID>> map;
  };
}

#include "entity id map.inl"

#endif
