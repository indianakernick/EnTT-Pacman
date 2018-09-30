//
//  movement.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_MOVEMENT_HPP
#define SYS_MOVEMENT_HPP

#include "core/maze.hpp"
#include "util/registry.hpp"

// This moves the entity into the next tile
void movement(Registry &);
// This makes sure that the entity can move in the DesiredDir and sets
// the ActualDir to be the same
void wallCollide(Registry &, const MazeState &);

#endif