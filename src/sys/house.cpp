//
//  house.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 29/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "house.hpp"

#include "comp/house.hpp"
#include "comp/target.hpp"
#include "comp/position.hpp"
#include "core/constants.hpp"
#include "comp/ghost_mode.hpp"
#include "comp/home_position.hpp"
#include <entt/entity/registry.hpp>

void enterHouse(entt::registry &reg) {
  const auto view = reg.view<EnterHouse, Position, HomePosition>();
  for (const entt::entity e : view) {
    if (view.get<Position>(e).p == view.get<HomePosition>(e).home) {
      reg.remove<EnterHouse>(e);
      reg.emplace<LeaveHouse>(e);
      reg.remove<EatenMode>(e);
      reg.emplace<ChaseMode>(e);
    }
  }
}

void leaveHouse(entt::registry &reg) {
  auto view = reg.view<LeaveHouse, Position, Target>();
  for (const entt::entity e : view) {
    if (view.get<Position>(e).p == outsideHouse) {
      reg.remove<LeaveHouse>(e);
    } else {
      // leaveHouse is called after the set*Target systems so this will
      // overwrite the target position. It's a little bit hacky but it
      // works here.

      // We actually need to do this because ghosts can sometimes get stuck
      // in the house. If their target is towards the bottom of the maze,
      // they will move left and right without going up and out of the house
      view.get<Target>(e).p = outsideHouse;
    }
  }
}
