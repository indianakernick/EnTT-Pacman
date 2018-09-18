//
//  factories.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "factories.hpp"

#include "sprites.hpp"
#include "player component.hpp"
#include "sprite component.hpp"
#include "position component.hpp"

Entity makePlayer(Registry &reg, const Grid::Pos pos) {
  const Entity e = reg.create();
  reg.assign<Player>(e);
  reg.assign<Sprite>(e, makePlayer());
  reg.assign<Position>(e, pos);
  return e;
}

Entity makeRock(Registry &reg, const Grid::Pos pos) {
  const Entity e = reg.create();
  reg.assign<Sprite>(e, makeRock());
  reg.assign<Position>(e, pos);
  return e;
}