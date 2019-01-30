//
//  movement.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "movement.hpp"

#include "comp/dir.hpp"
#include "util/dir2vec.hpp"
#include "sys/can_move.hpp"
#include "comp/position.hpp"

void movement(Registry &reg) {
  auto view = reg.view<Position, ActualDir>();
  for (const Entity e : view) {
    Grid::Pos &pos = view.get<Position>(e).p;
    const Grid::Dir dir = view.get<ActualDir>(e).d;
    pos += toVec(dir);

    // The tunnel.
    // This assumes the exact position of the tunnel.
    // It's good enough for this simple game but a more robust solution might
    // involve making the tunnel into an entity
    if (pos.y == 10) {
      if (pos.x <= -1 && dir == Grid::Dir::left) {
        pos.x = 19;
      } else if (pos.x >= 19 && dir == Grid::Dir::right) {
        pos.x = -1;
      }
    }
  }
}

void wallCollide(Registry &reg, const MazeState &maze) {
  auto view = reg.view<Position, ActualDir, DesiredDir>();
  for (const Entity e : view) {
    const Grid::Pos pos = view.get<Position>(e).p;
    const Grid::Dir desiredDir = view.get<DesiredDir>(e).d;
    if (canMove(reg, maze, e, pos, desiredDir)) {
      view.get<ActualDir>(e).d = desiredDir;
      continue;
    }

    const Grid::Dir prevDir = view.get<ActualDir>(e).d;
    if (canMove(reg, maze, e, pos, prevDir)) {
      continue;
    }
    
    view.get<ActualDir>(e).d = Grid::Dir::none;
  }
}
