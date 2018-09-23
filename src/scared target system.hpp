//
//  scared target system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SCARED_TARGET_SYSTEM_HPP
#define SCARED_TARGET_SYSTEM_HPP

#include <random>
#include "maze.hpp"
#include "registry.hpp"

void scaredTarget(Registry &, const MazeState &, std::mt19937 &);

#endif