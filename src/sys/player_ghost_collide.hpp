//
//  player_ghost_collide.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 29/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_PLAYER_GHOST_COLLIDE_HPP
#define SYS_PLAYER_GHOST_COLLIDE_HPP

#include <entt/entity/fwd.hpp>

struct GhostCollision {
  entt::entity ghost;
  enum class Type {
    none, // no collision
    eat,  // ghost was eaten
    lose  // player lost
  } type;
};

// Deals with the player colliding with ghosts. If the ghost is in scared mode,
// the ghost is said to be eaten. The ID of the eaten ghost is returned so that
// the mode of the ghost can be changed by the change_ghost_mode system.
// If the ghost is in scatter or chase mode, the player has lost the game.
// If the ghost is in eaten mode, the player will pass straight through the ghost

GhostCollision playerGhostCollide(entt::registry &);

#endif
