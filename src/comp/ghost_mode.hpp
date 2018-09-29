//
//  ghost_mode.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_GHOST_MODE_HPP
#define COMP_GHOST_MODE_HPP

#include "core/constants.hpp"

struct ChaseMode {};
struct ScatterMode {};
struct ScaredMode {
  int timer = ghostScaredTime;
};
struct EatenMode {};

#endif