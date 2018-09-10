//
//  json.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline void ECS::insertPairs(EntityIDmap &map, const json &node, Registry &registry) {
  for (auto entity : node) {
    if (JSON_OPTIONAL(idNode, entity, "id")) {
      map.insertPair(idNode->get<ClientEntityID>(), registry.create());
    } else {
      map.insertNullPair(registry.create());
    }
  }
}
