//
//  set chase target system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SET_CHASE_TARGET_SYSTEM_HPP
#define SET_CHASE_TARGET_SYSTEM_HPP

#include "registry.hpp"

// These systems calculate the target position of ghosts in chase mode
// There is a system for each ghost because each ghost behaves differently
// The Target component is set for entities that have the ChaseMode component

void setBlinkyChaseTarget(Registry &);
void setPinkyChaseTarget(Registry &);
void setInkyChaseTarget(Registry &);
void setClydeChaseTarget(Registry &);

#endif