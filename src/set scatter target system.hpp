//
//  set scatter target system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SET_SCATTER_TARGET_SYSTEM_HPP
#define SET_SCATTER_TARGET_SYSTEM_HPP

#include "registry.hpp"

// This system calculates the target position of ghosts in scatter mode
// Each ghost has a "home corner" which is stored in the HomePosition component
// Ghosts will simply move towards their home corner and end up going round
// in circles

void setScatterTarget(Registry &);

#endif