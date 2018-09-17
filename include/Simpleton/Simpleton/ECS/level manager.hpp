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
#include "registry.hpp"
#include "comp inits.hpp"

namespace ECS {
  template <typename CompList>
  class LevelManager {
  public:
    using LevelPathGetter = std::function<std::string (ECS::Level)>;
  
    LevelManager() = default;
    
    void init(ECS::Registry &, const ECS::CompInits<CompList> &);
    void quit();
    
    bool loadLevel(ECS::Level);
    bool loadFinalLevel();
    bool nextLevel();
    bool reload();
    ECS::Level getLoaded() const;
    bool isLoaded() const;
    
    void levelPath(const LevelPathGetter &);

  private:
    ECS::Registry *registry = nullptr;
    const ECS::CompInits<CompList> *compInits = nullptr;
    std::function<std::string(ECS::Level)> getLevelPath;
    ECS::Level current = NULL_LEVEL;
  };
}

#include "level manager.inl"

#endif
