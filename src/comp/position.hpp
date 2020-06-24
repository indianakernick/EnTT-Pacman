//
//  position.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 18/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef COMP_POSITION_HPP
#define COMP_POSITION_HPP

#include "util/pos.hpp"

// The position of the tile that the entity is currently in.
// Between ticks, each entity animates from this tile to an adjacent tile

struct Position {
  Pos p;
};

#endif
