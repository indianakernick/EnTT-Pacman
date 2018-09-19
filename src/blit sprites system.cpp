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

void blitSprites(Registry &reg, FrameBuf &screen, const Grid::Pos camera) {
  const auto view = reg.view<Sprite, Position>();
  for (const Entity e : view) {
    const FrameBuf &sprite = view.get<Sprite>(e).s;
  	blit(screen, sprite, view.get<Position>(e).p + camera - sprite.size() / 2);
  }
}