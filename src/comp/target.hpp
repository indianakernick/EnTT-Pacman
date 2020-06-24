//
//  target.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 22/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef COMP_TARGET_HPP
#define COMP_TARGET_HPP

#include "util/pos.hpp"

// This is the target that a ghost is aiming for. If Blinky is in chase mode
// then his target is set to the player position.
// The pursue_target system will read this target and move the ghost towards it

struct Target {
  Pos p;
};

#endif
