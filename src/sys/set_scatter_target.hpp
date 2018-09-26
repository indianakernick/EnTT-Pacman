//
//  set_scatter_target.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_SET_SCATTER_TARGET_HPP
#define SYS_SET_SCATTER_TARGET_HPP

#include "util/registry.hpp"

// This system calculates the target position of ghosts in scatter mode
// Each ghost has a "home corner" which is stored in the HomePosition component
// Ghosts will simply move towards their home corner and end up going round
// in circles

void setScatterTarget(Registry &);

#endif