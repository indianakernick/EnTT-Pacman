//
//  level manager.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 31/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <cassert>
#include <fstream>
#include "json.hpp"
#include "entity id map.hpp"
#include "../Type List/get.hpp"

namespace ECS::detail {
  template <typename CompList>
  void loadComps(
    const ECS::EntityID id,
    const json &comps,
    const ECS::EntityIDmap &idMap,
    const ECS::CompInits<CompList> &compInits,
    ECS::Registry &registry
  ) {
    const json::object_t &obj = comps.get_ref<const json::object_t &>();
    for (auto &pair : obj) {
      const bool gotComp = List::getByName<CompList>(
        pair.first,
        [id, &idMap, &registry, &compInits, &props = pair.second] (auto t) {
          compInits.init(registry.assign<LIST_TYPE(t)>(id), props, idMap, id);
        }
      );
      if (!gotComp) {
        throw std::runtime_error(
          "Unknown component name \""
          + pair.first
          + "\""
        );
      }
    }
  }

  template <typename CompList>
  bool loadLevel(
    const std::string &fileName,
    const ECS::CompInits<CompList> &compInits,
    ECS::Registry &registry
  ) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
      return false;
    }
    json root;
    file >> root;
    
    ECS::EntityIDmap idMap;
    ECS::insertPairs(idMap, root, registry);
    
    for (size_t i = 0; i != root.size(); ++i) {
      const ECS::EntityID id = idMap.getEntityFromIndex(i);
      const json &node = root[i];
      
      if (JSON_OPTIONAL(compsNode, node, "components")) {
        loadComps(id, *compsNode, idMap, compInits, registry);
      }
    }
    
    return true;
  }
}

template <typename CompList>
void ECS::LevelManager<CompList>::init(
  ECS::Registry &newRegistry,
  const ECS::CompInits<CompList> &newCompInits
) {
  assert(!registry);
  registry = &newRegistry;
  compInits = &newCompInits;
}

template <typename CompList>
void ECS::LevelManager<CompList>::quit() {
  assert(registry);
  compInits = nullptr;
  registry = nullptr;
}

template <typename CompList>
bool ECS::LevelManager<CompList>::loadLevel(const ECS::Level level) {
  assert(registry);
  assert(getLevelPath);
  if (current != NULL_LEVEL) {
    registry->reset();
  }
  if (detail::loadLevel(getLevelPath(level), *compInits, *registry)) {
    current = level;
    return true;
  } else {
    return false;
  }
}

template <typename CompList>
bool ECS::LevelManager<CompList>::loadFinalLevel() {
  return loadLevel(FINAL_LEVEL);
}

template <typename CompList>
bool ECS::LevelManager<CompList>::nextLevel() {
  if (current == NULL_LEVEL) {
    return loadLevel(0);
  } else {
    if (loadLevel(current + 1)) {
      return true;
    } else {
      return loadFinalLevel();
    }
  }
}

template <typename CompList>
bool ECS::LevelManager<CompList>::reload() {
  if (current != NULL_LEVEL) {
    loadLevel(current);
    return true;
  } else {
    return false;
  }
}

template <typename CompList>
ECS::Level ECS::LevelManager<CompList>::getLoaded() const {
  return current;
}

template <typename CompList>
bool ECS::LevelManager<CompList>::isLoaded() const {
  return current != NULL_LEVEL;
}

template <typename CompList>
void ECS::LevelManager<CompList>::levelPath(const LevelPathGetter &newGetter) {
  getLevelPath = newGetter;
}
