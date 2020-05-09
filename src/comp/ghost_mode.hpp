//
//  ghost_mode.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 23/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef COMP_GHOST_MODE_HPP
#define COMP_GHOST_MODE_HPP

#include "core/constants.hpp"

// Tag types for the ghost modes. This is a better alternative to an enum.
// Creating a struct for each mode means that we store data specific to
// the mode. ScaredMode stores a timer. That timer only makes sense when
// the ghost is in ScaredMode. I could have used a std::variant but I think
// this is cleaner

struct ChaseMode {};
struct ScatterMode {};
struct ScaredMode {
  // This timer counts down the number of ticks that the ghost is scared for.
  // Once the timer reaches zero, the ghost enters chase mode. This is handled
  // by the change_ghost_mode systems
  int timer = ghostScaredTime;
};
struct EatenMode {};

#endif
