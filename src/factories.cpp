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
#include "actual dir component.hpp"
#include "desired dir component.hpp"
#include "maze sprite component.hpp"
#include "inky target component.hpp"
#include "ghost sprite component.hpp"
#include "clyde target component.hpp"
#include "pinky target component.hpp"
#include "player sprite component.hpp"
#include "blinky target component.hpp"

Entity makeMaze(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<MazeSprite>(e, sheet.getIDfromName("maze"));
  return e;
}

Entity makePlayer(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<Player>(e);
  reg.assign<DesiredDir>(e, Grid::Dir::left);
  reg.assign<ActualDir>(e, Grid::Dir::left);
  reg.assign<Position>(e, Grid::Pos{9, 16});
  reg.assign<PlayerSprite>(e, sheet.getIDfromName("pacman 0"));
  return e;
}

namespace {

Entity makeGhost(Registry &reg, const Grid::Pos pos) {
  const Entity e = reg.create();
  reg.assign<Position>(e, pos);
  reg.assign<DesiredDir>(e);
  reg.assign<ActualDir>(e);
  reg.assign<Target>(e);
  return e;
}

}

Entity makeBlinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, {9, 8});
  reg.assign<BlinkyTarget>(e, player);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("blinky 0"));
  return e;
}

Entity makePinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, {9, 10});
  reg.assign<PinkyTarget>(e, player);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("pinky 0"));
  return e;
}

Entity makeInky(
  Registry &reg,
  const Sprite::Sheet &sheet,
  const Entity player,
  const Entity blinky
) {
  const Entity e = makeGhost(reg, {8, 10});
  reg.assign<InkyTarget>(e, player, blinky);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("inky 0"));
  return e;
}

Entity makeClyde(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, {10, 10});
  reg.assign<ClydeTarget>(e, player);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("clyde 0"));
  return e;
}