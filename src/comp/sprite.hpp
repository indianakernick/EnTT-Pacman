//
//  sprite.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef COMP_SPRITE_HPP
#define COMP_SPRITE_HPP

#include "util/sprites.hpp"

// Sprite components just store a sprite ID.
// Rendering systems make assumptions about the animation and the
// layout of frames

struct PlayerSprite {
  animera::SpriteID id;
};

struct GhostSprite {
  animera::SpriteID id;
};

#endif
