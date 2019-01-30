//
//  player_ghost_collide.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "player_ghost_collide.hpp"

#include "comp/dir.hpp"
#include "comp/ghost.hpp"
#include "comp/player.hpp"
#include "util/dir2vec.hpp"
#include "comp/position.hpp"
#include "comp/ghost_mode.hpp"

namespace {

bool collide(
  const Grid::Pos pPos, 
  const Grid::Pos gPos, 
  const Grid::Dir pDir,
  const Grid::Dir gDir
) {
  if (pPos == gPos) {
    return true;
  }
  if (pPos + toVec(pDir) != gPos) {
    return false;
  }
  if (pDir != Grid::opposite(gDir)) {
    return false;
  }
  return true;
}

}

GhostCollision playerGhostCollide(Registry &reg) {
  const auto players = reg.view<Player, Position, ActualDir>();
  const auto ghosts = reg.view<Ghost, Position, ActualDir>();
  for (const Entity p : players) {
    const Grid::Pos playerPos = players.get<Position>(p).p;
    const Grid::Dir playerDir = players.get<ActualDir>(p).d;
    for (const Entity g : ghosts) {
      const Grid::Pos ghostPos = ghosts.get<Position>(g).p;
      const Grid::Dir ghostDir = ghosts.get<ActualDir>(g).d;
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
