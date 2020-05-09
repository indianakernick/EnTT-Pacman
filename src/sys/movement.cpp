//
//  movement.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 18/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "movement.hpp"

#include "comp/dir.hpp"
#include "util/dir_to_pos.hpp"
#include "sys/can_move.hpp"
#include "comp/position.hpp"
#include <entt/entity/registry.hpp>

void movement(entt::registry &reg) {
  auto view = reg.view<Position, ActualDir>();
  for (const entt::entity e : view) {
    Pos &pos = view.get<Position>(e).p;
    const Dir dir = view.get<ActualDir>(e).d;
    pos += toPos(dir);

    // The tunnel.
    // This assumes the exact position of the tunnel.
    // It's good enough for this simple game but a more robust solution might
    // involve making the tunnel into an entity
    if (pos.y == 10) {
      if (pos.x <= -1 && dir == Dir::left) {
        pos.x = 19;
      } else if (pos.x >= 19 && dir == Dir::right) {
        pos.x = -1;
      }
    }
  }
}

void wallCollide(entt::registry &reg, const MazeState &maze) {
  auto view = reg.view<Position, ActualDir, DesiredDir>();
  for (const entt::entity e : view) {
    const Pos pos = view.get<Position>(e).p;
    const Dir desiredDir = view.get<DesiredDir>(e).d;
    if (canMove(reg, maze, e, pos, desiredDir)) {
      view.get<ActualDir>(e).d = desiredDir;
      continue;
    }

    const Dir prevDir = view.get<ActualDir>(e).d;
    if (canMove(reg, maze, e, pos, prevDir)) {
      continue;
    }
    
    view.get<ActualDir>(e).d = Dir::none;
  }
}
