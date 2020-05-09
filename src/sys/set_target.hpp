//
//  set_target.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_SET_TARGET_HPP
#define SYS_SET_TARGET_HPP

#include <random>
#include "core/maze.hpp"
#include <entt/entity/fwd.hpp>

// These systems calculate the target position of ghosts.
// Each ghost has a different target depending on which mode it's in.

// There is a chase target system for each ghost because each ghost
// behaves differently in chase mode.
void setBlinkyChaseTarget(entt::registry &);
void setPinkyChaseTarget(entt::registry &);
void setInkyChaseTarget(entt::registry &);
void setClydeChaseTarget(entt::registry &);

// Each ghost has a "home corner" which is stored in the HomePosition component
// Ghosts will simply move towards their home corner and end up going round
// in circles
void setScatterTarget(entt::registry &);

// Ghosts move randomly in scared mode so we pass in a std::mt19937 for
// random numbers
void setScaredTarget(entt::registry &, const MazeState &, std::mt19937 &);

// When a ghost is eaten, their eyes will return the ghost house to be revived
void setEatenTarget(entt::registry &);

#endif
