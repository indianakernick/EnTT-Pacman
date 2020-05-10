//
//  eat_dots.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 22/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "eat_dots.hpp"

#include "comp/player.hpp"
#include "comp/position.hpp"
#include <entt/entity/registry.hpp>

namespace {

int countConsumptions(entt::registry &reg, MazeState &maze, const Tile food) {
  int count = 0;
  const auto view = reg.view<Player, Position>();
  for (const entt::entity e : view) {
    const Pos pos = view.get<Position>(e).p;
    if (maze.outOfRange(pos)) {
      continue;
    }
    Tile &tile = maze[pos];
    if (tile == food) {
      ++count;
      tile = Tile::empty;
    }
  }
  return count;
}

}

int eatDots(entt::registry &reg, MazeState &maze) {
  return countConsumptions(reg, maze, Tile::dot);
}

bool eatEnergizer(entt::registry &reg, MazeState &maze) {
  return countConsumptions(reg, maze, Tile::energizer);
}
