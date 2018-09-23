//
//  factories.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "factories.hpp"

#include "player component.hpp"
#include "target component.hpp"
#include "position component.hpp"
#include "sprite id component.hpp"
#include "actual dir component.hpp"
#include "desired dir component.hpp"
#include "maze sprite component.hpp"
#include "inky target component.hpp"
#include "ghost sprite component.hpp"
#include "pinky target component.hpp"
#include "blinky target component.hpp"

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

namespace {

Entity makeGhost(Registry &reg) {
  const Entity e = reg.create();
  reg.assign<GhostSprite>(e);
  reg.assign<DesiredDir>(e);
  reg.assign<ActualDir>(e);
  reg.assign<Target>(e);
  return e;
}

}

Entity makeBlinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg);
  reg.assign<BlinkyTarget>(e, player);
  reg.assign<Position>(e, Grid::Pos{9, 8});
  reg.assign<SpriteID>(e, sheet.getIDfromName("blinky 0"));
  return e;
}

Entity makePinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg);
  reg.assign<PinkyTarget>(e, player);
  reg.assign<Position>(e, Grid::Pos{9, 6});
  reg.assign<SpriteID>(e, sheet.getIDfromName("pinky 0"));
  return e;
}

Entity makeInky(
  Registry &reg,
  const Sprite::Sheet &sheet,
  const Entity player,
  const Entity blinky
) {
  const Entity e = makeGhost(reg);
  reg.assign<InkyTarget>(e, player, blinky);
  reg.assign<Position>(e, Grid::Pos{8, 6});
  reg.assign<SpriteID>(e, sheet.getIDfromName("inky 0"));
  return e;
}