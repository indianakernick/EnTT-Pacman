//
//  sprite.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_SPRITE_HPP
#define COMP_SPRITE_HPP

#include <Simpleton/Sprite/id.hpp>

// Sprite components just store a sprite ID.
// Rendering systems make assumptions about the animation and the
// layout of frames

struct PlayerSprite {
  Sprite::ID id;
};

struct GhostSprite {
  Sprite::ID id;
  Sprite::ID scared;
  Sprite::ID eyes;
};

#endif