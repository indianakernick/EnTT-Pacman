//
//  factories.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 18/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
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

entt::entity makePlayer(entt::registry &reg) {
  const entt::entity e = reg.create();
  reg.emplace<Player>(e);
  reg.emplace<DesiredDir>(e, playerSpawnDir);
  reg.emplace<ActualDir>(e, playerSpawnDir);
  reg.emplace<Position>(e, playerSpawnPos);
  reg.emplace<PlayerSprite>(e, animera::SpriteID::pacman_beg_);
  return e;
}

namespace {

entt::entity makeGhost(entt::registry &reg, const Pos home, const Pos scatter) {
  const entt::entity e = reg.create();
  reg.emplace<Position>(e, home);
  reg.emplace<HomePosition>(e, home, scatter);
  reg.emplace<LeaveHouse>(e);
  reg.emplace<ScatterMode>(e);
  reg.emplace<DesiredDir>(e);
  reg.emplace<ActualDir>(e);
  reg.emplace<Target>(e);
  reg.emplace<Ghost>(e);
  return e;
}

}

entt::entity makeBlinky(entt::registry &reg, const entt::entity player) {
  const entt::entity e = makeGhost(reg, blinkyHome, blinkyScatter);
  reg.get<Position>(e).p = outsideHouse;
  reg.emplace<BlinkyChaseTarget>(e, player);
  reg.emplace<GhostSprite>(e, animera::SpriteID::blinky_beg_);
  return e;
}

entt::entity makePinky(entt::registry &reg, const entt::entity player) {
  const entt::entity e = makeGhost(reg, pinkyHome, pinkyScatter);
  reg.emplace<PinkyChaseTarget>(e, player);
  reg.emplace<GhostSprite>(e, animera::SpriteID::pinky_beg_);
  return e;
}

entt::entity makeInky(
  entt::registry &reg,
  const entt::entity player,
  const entt::entity blinky
) {
  const entt::entity e = makeGhost(reg, inkyHome, inkyScatter);
  reg.emplace<InkyChaseTarget>(e, player, blinky);
  reg.emplace<GhostSprite>(e, animera::SpriteID::inky_beg_);
  return e;
}

entt::entity makeClyde(entt::registry &reg, const entt::entity player) {
  const entt::entity e = makeGhost(reg, clydeHome, clydeScatter);
  reg.emplace<ClydeChaseTarget>(e, player);
  reg.emplace<GhostSprite>(e, animera::SpriteID::clyde_beg_);
  return e;
}
