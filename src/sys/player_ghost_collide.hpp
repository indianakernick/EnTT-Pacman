//
//  player_ghost_collide.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_PLAYER_GHOST_COLLIDE_HPP
#define SYS_PLAYER_GHOST_COLLIDE_HPP

#include "util/registry.hpp"

struct GhostCollision {
  Entity ghost;
  enum class Type {
  	none, // no collision
  	eat,  // ghost was eaten
  	lose  // player lost
  } type;
};

GhostCollision playerGhostCollide(Registry &);

#endif