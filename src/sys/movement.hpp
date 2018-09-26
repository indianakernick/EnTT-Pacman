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

void movement(Registry &);
void wallCollide(Registry &, const MazeState &);

#endif