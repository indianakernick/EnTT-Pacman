//
//  can_move.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 27/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_CAN_MOVE_HPP
#define SYS_CAN_MOVE_HPP

#include "util/dir.hpp"
#include "core/maze.hpp"
#include <entt/entity/fwd.hpp>

// Checks whether an entity can move in some direction.
// Deals with ghosts entering and leaving the house

bool canMove(entt::registry &, const MazeState &, entt::entity, Pos, Dir);

#endif
