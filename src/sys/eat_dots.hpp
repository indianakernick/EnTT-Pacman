//
//  eat_dots.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_EAT_DOTS_HPP
#define SYS_EAT_DOTS_HPP

#include "core/maze.hpp"
#include "util/registry.hpp"

// Returns the number of dots that the player ate (usually 0 or 1)
int eatDots(Registry &, MazeState &);
// Returns whether the player collided with an energizer
bool eatEnergizer(Registry &, MazeState &);

#endif
