//
//  factories.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "factories.hpp"

#include "player component.hpp"
#include "position component.hpp"
#include "sprite id component.hpp"
#include "desired dir component.hpp"

/*

Entity makePlayer(Registry &reg, const Grid::Pos pos) {
  const Entity e = makeObject(reg, pos, makePlayerSprite());
  reg.assign<Player>(e);
  return e;
}

Entity makeGhost(Registry &reg, const Grid::Pos pos, const FrameBuf &sprite) {
  const Entity e = makeObject(reg, pos, sprite);
  reg.assign<RandomDir>(e);
  return e;
}

Entity makeObject(Registry &reg, const Grid::Pos pos, const FrameBuf &sprite) {
  const Entity e = reg.create();
  reg.assign<Sprite>(e, sprite);
  reg.assign<Position>(e, pos);
  reg.assign<DesiredDir>(e);
  return e;
}

*/