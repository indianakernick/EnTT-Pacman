//
//  comp init.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_comp_init_hpp
#define engine_ecs_comp_init_hpp

#include "../Data/json.hpp"
#include <entt/entity/registry.hpp>

namespace ECS {
  class EntityIDmap;
  
  template <typename Comp_>
  class CompInit {
  public:
    using Comp = Comp_;

    CompInit() = default;
    virtual ~CompInit() = default;
    
    void initialize(Comp &comp, const json &node, const EntityIDmap &idMap, const entt::entity entity) {
      init(comp, node, idMap, entity);
    }

  private:
    virtual void init(Comp &comp, const json &node, const EntityIDmap &idMap, entt::entity) {
      init(comp, node, idMap);
    }
    virtual void init(Comp &comp, const json &node, const EntityIDmap &) {
      init(comp, node);
    }
    virtual void init(Comp &comp, const json &) {
      init(comp);
    }
    virtual void init(Comp &) {}
  };
}

#endif
