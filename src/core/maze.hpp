//
//  maze.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef CORE_MAZE_HPP
#define CORE_MAZE_HPP

#include <Simpleton/Grid/grid.hpp>

enum class Tile : uint8_t {
  empty,
  dot,
  energizer,
  wall,
  door
};

using MazeState = Grid::Grid<Tile>;

MazeState makeMazeState(); 

#endif
