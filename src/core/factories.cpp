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
#include <entt/entity/registry.hpp>

entt::entity makePlayer(entt::registry &reg, const SpriteSheet &sheet) {
  const entt::entity e = reg.create();
  reg.assign<Player>(e);
  reg.assign<DesiredDir>(e, playerSpawnDir);
  reg.assign<ActualDir>(e, playerSpawnDir);
  reg.assign<Position>(e, playerSpawnPos);
  reg.assign<PlayerSprite>(e, sheet.lookup("pacman 0"));
  return e;
}

namespace {

entt::entity makeGhost(entt::registry &reg, const Pos home, const Pos scatter) {
  const entt::entity e = reg.create();
  reg.assign<Position>(e, home);
  reg.assign<HomePosition>(e, home, scatter);
  reg.assign<LeaveHouse>(e);
  reg.assign<ScatterMode>(e);
  reg.assign<DesiredDir>(e);
  reg.assign<ActualDir>(e);
  reg.assign<Target>(e);
  reg.assign<Ghost>(e);
  return e;
}

GhostSprite makeGhostSprite(const SpriteSheet &sheet, const std::string_view name) {
  GhostSprite sprite;
  sprite.id = sheet.lookup(name);
  sprite.scared = sheet.lookup("scared 0");
  sprite.eyes = sheet.lookup("eyes 0");
  return sprite;
}

}

entt::entity makeBlinky(entt::registry &reg, const SpriteSheet &sheet, const entt::entity player) {
  const entt::entity e = makeGhost(reg, blinkyHome, blinkyScatter);
  reg.get<Position>(e).p = outsideHouse;
  reg.assign<BlinkyChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "blinky 0"));
  return e;
}

entt::entity makePinky(entt::registry &reg, const SpriteSheet &sheet, const entt::entity player) {
  const entt::entity e = makeGhost(reg, pinkyHome, pinkyScatter);
  reg.assign<PinkyChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "pinky 0"));
  return e;
}

entt::entity makeInky(
  entt::registry &reg,
  const SpriteSheet &sheet,
  const entt::entity player,
  const entt::entity blinky
) {
  const entt::entity e = makeGhost(reg, inkyHome, inkyScatter);
  reg.assign<InkyChaseTarget>(e, player, blinky);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "inky 0"));
  return e;
}

entt::entity makeClyde(entt::registry &reg, const SpriteSheet &sheet, const entt::entity player) {
  const entt::entity e = makeGhost(reg, clydeHome, clydeScatter);
  reg.assign<ClydeChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, makeGhostSprite(sheet, "clyde 0"));
  return e;
}
