//
//  can_move.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 27/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_CAN_MOVE_HPP
#define SYS_CAN_MOVE_HPP

#include "core/maze.hpp"
#include "util/registry.hpp"
#include <Simpleton/Grid/dir.hpp>

// Checks whether an entity can move in some direction.
// Deals with ghosts entering and leaving the house

bool canMove(Registry &, const MazeState &, Entity, Grid::Pos, Grid::Dir);

#endif