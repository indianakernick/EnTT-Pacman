//
//  change_ghost_mode.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 29/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "change_ghost_mode.hpp"

#include "comp/house.hpp"
#include "comp/ghost.hpp"
#include "comp/ghost_mode.hpp"
#include <entt/entity/registry.hpp>

void ghostScared(entt::registry &reg) {
  const auto view = reg.view<Ghost>();
  for (const entt::entity e : view) {
    if (reg.has<ChaseMode>(e)) {
      reg.remove<ChaseMode>(e);
    } else if (reg.has<ScatterMode>(e)) {
      reg.remove<ScatterMode>(e);
    } else if (reg.has<ScaredMode>(e)) {
      reg.remove<ScaredMode>(e);
    } else {
      continue; // Ghosts in EatenMode don't get scared
    }
    reg.assign<ScaredMode>(e);
  }
}

void ghostScaredTimeout(entt::registry &reg) {
  auto view = reg.view<Ghost, ScaredMode>();
  for (const entt::entity e : view) {
    ScaredMode &scared = view.get<ScaredMode>(e);
    --scared.timer;
    if (scared.timer <= 0) {
      // Adding and removing components from the entity that is currently
      // returned by the view is OK
      reg.remove<ScaredMode>(e);
      reg.assign<ChaseMode>(e);
    }
  }
}

void ghostEaten(entt::registry &reg, const entt::entity ghost) {
  reg.remove<ScaredMode>(ghost);
  reg.assign<EatenMode>(ghost);
  reg.assign<EnterHouse>(ghost);
}

void ghostScatter(entt::registry &reg) {
  const auto view = reg.view<Ghost, ChaseMode>();
  for (const entt::entity e : view) {
    reg.remove<ChaseMode>(e);
    reg.assign<ScatterMode>(e);
  }
}

void ghostChase(entt::registry &reg) {
  const auto view = reg.view<Ghost, ScatterMode>();
  for (const entt::entity e : view) {
    reg.remove<ScatterMode>(e);
    reg.assign<ChaseMode>(e);
  }
}
