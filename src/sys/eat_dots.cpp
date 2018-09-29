//
//  eat_dots.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "eat_dots.hpp"

#include "comp/player.hpp"
#include "comp/position.hpp"

namespace {

int countConsumptions(Registry &reg, MazeState &maze, const Tile food) {
  int count = 0;
  const auto view = reg.view<Player, Position>();
  for (const Entity e : view) {
    const Grid::Pos pos = view.get<Position>(e).p;
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

int eatDots(Registry &reg, MazeState &maze) {
  return countConsumptions(reg, maze, Tile::dot);
}

bool eatEnergizer(Registry &reg, MazeState &maze) {
  return countConsumptions(reg, maze, Tile::energizer);
}