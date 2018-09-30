//
//  set_target.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_SET_TARGET_HPP
#define SYS_SET_TARGET_HPP

#include <random>
#include "core/maze.hpp"
#include "util/registry.hpp"

// These systems calculate the target position of ghosts.
// Each ghost has a different target depending on which mode it's in.

// There is a chase target system for each ghost because each ghost
// behaves differently in chase mode.
void setBlinkyChaseTarget(Registry &);
void setPinkyChaseTarget(Registry &);
void setInkyChaseTarget(Registry &);
void setClydeChaseTarget(Registry &);

// Each ghost has a "home corner" which is stored in the HomePosition component
// Ghosts will simply move towards their home corner and end up going round
// in circles
void setScatterTarget(Registry &);

// Ghosts move randomly in scared mode so we pass in a std::mt19937 for
// random numbers
void setScaredTarget(Registry &, const MazeState &, std::mt19937 &);

// When a ghost is eaten, their eyes will return the ghost house to be revived
void setEatenTarget(Registry &);

#endif