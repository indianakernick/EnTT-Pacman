//
//  entity id map.cpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity id map.hpp"

inline void ECS::EntityIDmap::insertPair(const ClientEntityID client, const EntityID entity) {
  if (client == NULL_CLIENT_ENTITY_ID) {
    throw std::runtime_error("Usage of reserved user defined entity ID");
  }
  for (auto pair : map) {
    if (pair.first == client) {
      throw std::runtime_error("All user defined entity IDs must be unique or absent");
    }
  }
  
  map.emplace_back(client, entity);
}

inline void ECS::EntityIDmap::insertNullPair(const EntityID entity) {
  map.emplace_back(NULL_CLIENT_ENTITY_ID, entity);
}

inline ECS::EntityID ECS::EntityIDmap::getEntityFromIndex(const size_t i) const {
  if (i < map.size()) {
    return map[i].second;
  }
  throw std::runtime_error("Invalid index");
}

inline ECS::EntityID ECS::EntityIDmap::getEntityFromID(const ClientEntityID id) const {
  for (auto pair : map) {
    if (pair.first == id) {
      return pair.second;
    }
  }
  throw std::runtime_error("Invalid user ID");
}
