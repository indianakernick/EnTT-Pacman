//
//  set_scared_target.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_SET_SCARED_TARGET_HPP
#define SYS_SET_SCARED_TARGET_HPP

#include <random>
#include "core/maze.hpp"
#include "util/registry.hpp"

// This system calculates the target position of ghosts in scared mode
// Since all of the ghosts behave the same way in scared mode, there is one
// system for them all

// Ghosts move randomly in scared mode so we pass in a std::mt19937 for
// random numbers

void setScaredTarget(Registry &, const MazeState &, std::mt19937 &);

#endif