//
//  set scared target system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SET_SCARED_TARGET_SYSTEM_HPP
#define SET_SCARED_TARGET_SYSTEM_HPP

#include <random>
#include "maze.hpp"
#include "registry.hpp"

// This system calculates the target position of ghosts in scared mode
// Since all of the ghosts behave the same way in scared mode, there is one
// system for them all

// Ghosts move randomly in scared mode so we pass in a std::mt19937 for
// random numbers

void setScaredTarget(Registry &, const MazeState &, std::mt19937 &);

#endif