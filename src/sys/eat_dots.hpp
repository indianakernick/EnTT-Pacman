//
//  eat_dots.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 22/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_EAT_DOTS_HPP
#define SYS_EAT_DOTS_HPP

#include "core/maze.hpp"
#include <entt/entity/fwd.hpp>

// Returns the number of dots that the player ate (usually 0 or 1)
int eatDots(entt::registry &, MazeState &);

// Returns whether the player collided with an energizer
bool eatEnergizer(entt::registry &, MazeState &);

#endif
