//
//  maze.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef CORE_MAZE_HPP
#define CORE_MAZE_HPP

#include <cstdint>
#include "../util/grid.hpp"

enum class Tile : std::uint8_t {
  empty,
  dot,
  energizer,
  wall,
  door
};

using MazeState = Grid<Tile>;

MazeState makeMazeState(); 

#endif
