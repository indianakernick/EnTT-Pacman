//
//  entity id.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_entity_id_hpp
#define engine_box2d_entity_id_hpp

#include "../ECS/registry.hpp"

namespace B2 {
  inline void *getUserData(const ECS::EntityID entity) {
    return reinterpret_cast<void *>(
      static_cast<uintptr_t>(entity)
    );
  }

  inline ECS::EntityID getEntity(const void *const userData) {
    return static_cast<ECS::EntityID>(
      reinterpret_cast<uintptr_t>(userData)
    );
  }
}

#endif
