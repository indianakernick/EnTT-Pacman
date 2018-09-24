//
//  pursue target system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef PURSUE_TARGET_SYSTEM_HPP
#define PURSUE_TARGET_SYSTEM_HPP

#include "maze.hpp"
#include "registry.hpp"

// This system reads the target position from the Target component and pursues
// it by setting the DesiredDir component. Pacman doesn't use A*. Ghosts will
// turn in the direction that brings them closer to the player

void pursueTarget(Registry &, const MazeState &);

#endif