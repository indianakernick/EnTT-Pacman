//
//  sprite.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_SPRITE_HPP
#define COMP_SPRITE_HPP

#include "../util/sprite_id.hpp"

// Sprite components just store a sprite ID.
// Rendering systems make assumptions about the animation and the
// layout of frames

struct PlayerSprite {
  SpriteID id;
};

struct GhostSprite {
  SpriteID id;
  SpriteID scared;
  SpriteID eyes;
};

#endif
