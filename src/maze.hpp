//
//  maze.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef MAZE_HPP
#define MAZE_HPP

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