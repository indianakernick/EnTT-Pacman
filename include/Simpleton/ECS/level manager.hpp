//
//  level manager.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 31/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_level_manager_hpp
#define engine_ecs_level_manager_hpp

#include "level.hpp"
#include <functional>
#include "comp inits.hpp"
#include <entt/entity/registry.hpp>

namespace ECS {
  template <typename CompList>
  class LevelManager {
  public:
    using LevelPathGetter = std::function<std::string (ECS::Level)>;
  
    LevelManager() = default;
    
    void init(entt::registry &, const ECS::CompInits<CompList> &);
    void quit();
    
    bool loadLevel(ECS::Level);
    bool loadFinalLevel();
    bool nextLevel();
    bool reload();
    ECS::Level getLoaded() const;
    bool isLoaded() const;
    
    void levelPath(const LevelPathGetter &);

  private:
    entt::registry *registry = nullptr;
    const ECS::CompInits<CompList> *compInits = nullptr;
    std::function<std::string(ECS::Level)> getLevelPath;
    ECS::Level current = NULL_LEVEL;
  };
}

#include "level manager.inl"

#endif
