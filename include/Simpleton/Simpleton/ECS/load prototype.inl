//
//  load prototype.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "../Utils/type name.hpp"
#include "../Type List/foreach.hpp"

namespace ECS::detail {
  template <typename Comp>
  constexpr auto hasFromjson(int) -> decltype(from_json(json{}, std::declval<Comp &>()), bool{}) {
    return true;
  }

  template <typename Comp>
  constexpr bool hasFromjson(long) {
    return false;
  }

  template <typename CompList>
  bool loadComponent(
    ECS::Prototype &proto,
    const std::string_view name,
    const json &component
  ) {
    bool read = false;
    List::forEach<CompList>([&proto, name, &component, &read] (auto t) {
      using Comp = LIST_TYPE(t);
      if (Utils::typeName<Comp>() == name) {
        if constexpr (hasFromjson<Comp>(0)) {
          proto.set<Comp>(component.get<Comp>());
        } else {
          proto.set<Comp>();
        }
        read = true;
      }
    });
    return read;
  }
}

template <typename CompList>
int ECS::loadProto(ECS::Prototype &proto, const json &node) {
  const json::object_t &object = node.get_ref<const json::object_t &>();
  int unreadCount = 0;
  for (const auto &pair : object) {
    unreadCount += !detail::loadComponent<CompList>(proto, pair.first, pair.second);
  }
  return unreadCount;
}
