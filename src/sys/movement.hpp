//
//  movement.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 18/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_MOVEMENT_HPP
#define SYS_MOVEMENT_HPP

#include "core/maze.hpp"
#include <entt/entity/fwd.hpp>

// This moves the entity into the next tile
void movement(entt::registry &);

// This makes sure that the entity can move in the DesiredDir and sets
// the ActualDir to be the same
void wallCollide(entt::registry &, const MazeState &);

#endif
