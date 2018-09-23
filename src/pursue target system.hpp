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

// Read target position from Target and pursue it by setting DesiredDir
void pursueTarget(Registry &, const MazeState &);

#endif