//
//  factories.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "factories.hpp"

#include "comp/dir.hpp"
#include "constants.hpp"
#include "comp/house.hpp"
#include "comp/ghost.hpp"
#include "comp/sprite.hpp"
#include "comp/target.hpp"
#include "comp/player.hpp"
#include "comp/position.hpp"
#include "comp/ghost_mode.hpp"
#include "comp/chase_target.hpp"
#include "comp/home_position.hpp"

Entity makePlayer(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<Player>(e);
  reg.assign<DesiredDir>(e, playerSpawnDir);
  reg.assign<ActualDir>(e, playerSpawnDir);
  reg.assign<Position>(e, playerSpawnPos);
  reg.assign<PlayerSprite>(e, sheet.getIDfromName("pacman 0"));
  return e;
}

namespace {

Entity makeGhost(Registry &reg, const Grid::Pos home, const Grid::Pos scatter) {
  const Entity e = reg.create();
  reg.assign<ScatterMode>(e);
  reg.assign<Position>(e, home);
  reg.assign<DesiredDir>(e);
  reg.assign<ActualDir>(e);
  reg.assign<Target>(e);
  reg.assign<Ghost>(e);
  reg.assign<LeaveHouse>(e);
  reg.assign<HomePosition>(e, home, scatter);
  return e;
}

GhostSprite makeGhostSprite(const Sprite::Sheet &sheet, const std::string_view name) {
  GhostSprite sprite;
  sprite.id = sheet.getIDfromName(name);
  sprite.scared = sheet.getIDfromName("scared 0");
  sprite.eyes = sheet.getIDfromName("eyes 0");
  return sprite;
}

}

Entity makeBlinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, blinkyHome, blinkyScatter);
  reg.get<Position>(e).p = outsideHouse;
  reg.assign<BlinkyChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "blinky 0"));
  return e;
}

Entity makePinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, pinkyHome, pinkyScatter);
  reg.assign<PinkyChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "pinky 0"));
  return e;
}

Entity makeInky(
  Registry &reg,
  const Sprite::Sheet &sheet,
  const Entity player,
  const Entity blinky
) {
  const Entity e = makeGhost(reg, inkyHome, inkyScatter);
  reg.assign<InkyChaseTarget>(e, player, blinky);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "inky 0"));
  return e;
}

Entity makeClyde(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, clydeHome, clydeScatter);
  reg.assign<ClydeChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "clyde 0"));
  return e;
}
