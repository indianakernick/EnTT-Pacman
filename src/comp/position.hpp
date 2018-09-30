//
//  position.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_POSITION_HPP
#define COMP_POSITION_HPP

#include <Simpleton/Grid/pos.hpp>

// The position of the tile that the entity is currently in.
// Between ticks, each entity animates from this tile to an adjacent tile

struct Position {
  Grid::Pos p;
};

#endif