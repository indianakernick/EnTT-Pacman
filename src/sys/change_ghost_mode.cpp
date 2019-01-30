//
//  change_ghost_mode.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "change_ghost_mode.hpp"

#include "comp/house.hpp"
#include "comp/ghost.hpp"
#include "comp/ghost_mode.hpp"

void ghostScared(Registry &reg) {
  const auto view = reg.view<Ghost>();
  for (const Entity e : view) {
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

void ghostScaredTimeout(Registry &reg) {
  auto view = reg.view<Ghost, ScaredMode>();
  for (const Entity e : view) {
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

void ghostEaten(Registry &reg, const Entity ghost) {
  reg.remove<ScaredMode>(ghost);
  reg.assign<EatenMode>(ghost);
  reg.assign<EnterHouse>(ghost);
}

void ghostScatter(Registry &reg) {
  const auto view = reg.view<Ghost, ChaseMode>();
  for (const Entity e : view) {
    reg.remove<ChaseMode>(e);
    reg.assign<ScatterMode>(e);
  }
}

void ghostChase(Registry &reg) {
  const auto view = reg.view<Ghost, ScatterMode>();
  for (const Entity e : view) {
    reg.remove<ScatterMode>(e);
    reg.assign<ChaseMode>(e);
  }
}
