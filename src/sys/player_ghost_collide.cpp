//
//  player_ghost_collide.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 29/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "player_ghost_collide.hpp"

#include "comp/dir.hpp"
#include "comp/ghost.hpp"
#include "comp/player.hpp"
#include "comp/position.hpp"
#include "util/dir_to_pos.hpp"
#include "comp/ghost_mode.hpp"
#include <entt/entity/registry.hpp>

namespace {

bool collide(
  const Pos pPos,
  const Pos gPos,
  const Dir pDir,
  const Dir gDir
) {
  if (pPos == gPos)               return true;
  if (pPos + toPos(pDir) != gPos) return false;
  if (pDir != opposite(gDir))     return false;
  return true;
}

}

GhostCollision playerGhostCollide(entt::registry &reg) {
  const auto players = reg.view<Player, Position, ActualDir>();
  const auto ghosts = reg.view<Ghost, Position, ActualDir>();
  for (const entt::entity p : players) {
    const Pos playerPos = players.get<Position>(p).p;
    const Dir playerDir = players.get<ActualDir>(p).d;
    for (const entt::entity g : ghosts) {
      const Pos ghostPos = ghosts.get<Position>(g).p;
      const Dir ghostDir = ghosts.get<ActualDir>(g).d;
      if (collide(playerPos, ghostPos, playerDir, ghostDir)) {
        if (reg.has<ScaredMode>(g)) {
          return {g, GhostCollision::Type::eat};
        } else if (reg.has<EatenMode>(g)) {
          continue;
        }
        return {g, GhostCollision::Type::lose};
      }
    }
  }
  return {entt::null, GhostCollision::Type::none};
}
