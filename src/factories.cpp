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
#include "actual dir component.hpp"
#include "desired dir component.hpp"
#include "maze sprite component.hpp"
#include "ghost sprite component.hpp"

Entity makeMaze(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<SpriteID>(e, sheet.getIDfromName("maze"));
  reg.assign<MazeSprite>(e);
  return e;
}

Entity makePlayer(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<Player>(e);
  reg.assign<DesiredDir>(e, Grid::Dir::left);
  reg.assign<ActualDir>(e, Grid::Dir::left);
  reg.assign<Position>(e, Grid::Pos{9, 16});
  reg.assign<SpriteID>(e, sheet.getIDfromName("pacman 0"));
  return e;
}

Entity makeBlinky(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<GhostSprite>(e);
  reg.assign<DesiredDir>(e, Grid::Dir::left);
  reg.assign<ActualDir>(e, Grid::Dir::left);
  reg.assign<Position>(e, Grid::Pos{9, 8});
  reg.assign<SpriteID>(e, sheet.getIDfromName("blinky 0"));
  return e;
}