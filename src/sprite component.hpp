//
//  sprite component.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <Simpleton/Sprite/id.hpp>

struct PlayerSprite {
  Sprite::ID id;
};

struct GhostSprite {
  Sprite::ID id;
};

struct MazeSprite {
  Sprite::ID id;
};

#endif