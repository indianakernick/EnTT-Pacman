//
//  set_target.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "set_target.hpp"

#include "can_move.hpp"
#include "comp/dir.hpp"
#include "comp/target.hpp"
#include "comp/position.hpp"
#include "util/dir_to_pos.hpp"
#include "comp/ghost_mode.hpp"
#include "comp/chase_target.hpp"
#include "comp/home_position.hpp"
#include <entt/entity/registry.hpp>

void setBlinkyChaseTarget(entt::registry &reg) {
  auto view = reg.view<Target, ChaseMode, BlinkyChaseTarget>();
  for (const entt::entity e : view) {
    const entt::entity player = view.get<BlinkyChaseTarget>(e).player;
    view.get<Target>(e).p = reg.get<Position>(player).p;
  }
}

void setPinkyChaseTarget(entt::registry &reg) {
  auto view = reg.view<Target, ChaseMode, PinkyChaseTarget>();
  for (const entt::entity e : view) {
    const entt::entity player = view.get<PinkyChaseTarget>(e).player;
    const Pos playerPos = reg.get<Position>(player).p;
    const Dir playerDir = reg.get<ActualDir>(player).d;
    view.get<Target>(e).p = playerPos + toPos(playerDir, 4);
  }
}

void setInkyChaseTarget(entt::registry &reg) {
  auto view = reg.view<Target, ChaseMode, InkyChaseTarget>();
  for (const entt::entity e : view) {
    const InkyChaseTarget target = view.get<InkyChaseTarget>(e);
    const Pos playerPos = reg.get<Position>(target.player).p;
    const Dir playerDir = reg.get<ActualDir>(target.player).d;
    const Pos offset = playerPos + toPos(playerDir, 2);
    const Pos blinkyPos = reg.get<Position>(target.blinky).p;
    view.get<Target>(e).p = blinkyPos + (offset - blinkyPos) * 2;
  }
}

void setClydeChaseTarget(entt::registry &reg) {
  auto view = reg.view<
    Target, Position, ChaseMode, ClydeChaseTarget, HomePosition
  >();
  for (const entt::entity e : view) {
    const entt::entity player = view.get<ClydeChaseTarget>(e).player;
    const Pos playerPos = reg.get<Position>(player).p;
    const float dist = distance(playerPos, view.get<Position>(e).p);
    if (dist >= 8.0f) {
      view.get<Target>(e).p = playerPos;
    } else {
      view.get<Target>(e).p = view.get<HomePosition>(e).scatter;
    }
  }
}

void setScatterTarget(entt::registry &reg) {
  auto view = reg.view<Target, ScatterMode, HomePosition>();
  for (const entt::entity e : view) {
    view.get<Target>(e).p = view.get<HomePosition>(e).scatter;
  }
}

void setScaredTarget(entt::registry &reg, const MazeState &maze, std::mt19937 &rand) {
  auto view = reg.view<Target, Position, ScaredMode, ActualDir>();
  for (const entt::entity e : view) {
    const Pos pos = view.get<Position>(e).p;
    const Dir dir = view.get<ActualDir>(e).d;
    const Pos nextPos = pos + toPos(dir);
    std::uniform_int_distribution<int> dist(0, 3);
    Dir candDir = static_cast<Dir>(dist(rand));
    Pos candPos = nextPos;

    for (int i = 0; i != 4; ++i) {
      if (candDir == opposite(dir)) {
        candDir = rotateCW(candDir);
        continue;
      }

      if (!canMove(reg, maze, e, nextPos, candDir)) {
        candDir = rotateCW(candDir);
        continue;
      }

      candPos = nextPos + toPos(candDir);
      break;
    }

    view.get<Target>(e).p = candPos;
  }
}

void setEatenTarget(entt::registry &reg) {
  auto view = reg.view<Target, EatenMode, HomePosition>();
  for (const entt::entity e : view) {
    view.get<Target>(e).p = view.get<HomePosition>(e).home;
  }
}
