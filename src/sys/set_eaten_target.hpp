//
//  set_eaten_target.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_SET_EATEN_TARGET_HPP
#define SYS_SET_EATEN_TARGET_HPP

#include "util/registry.hpp"

// This system calculates the target position of ghosts in eaten mode
// When a ghost is eaten, their eyes will return the ghost house to be revived

void setEatenTarget(Registry &);

#endif