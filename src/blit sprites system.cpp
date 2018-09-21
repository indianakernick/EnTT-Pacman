//
//  blit sprites system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "blit sprites system.hpp"

#include "sprite component.hpp"
#include "position component.hpp"

void blitSprites(Registry &reg) {
  const auto view = reg.view<Sprite, Position>();
  for (const Entity e : view) {

  }
}