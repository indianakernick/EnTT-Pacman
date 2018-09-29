//
//  player_lose.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "player_lose.hpp"

#include "comp/ghost.hpp"
#include "comp/player.hpp"
#include "comp/position.hpp"

bool playerLose(Registry &reg) {
  const auto players = reg.view<Player, Position>();
  const auto ghosts = reg.view<Ghost, Position>();
  for (const Entity p : players) {
    const Grid::Pos playerPos = players.get<Position>(p).p;
  	for (const Entity g : ghosts) {
  	  const Grid::Pos ghostPos = ghosts.get<Position>(g).p;
  	  if (playerPos == ghostPos) {
  	  	return true;
  	  }
  	}
  }
  return false;
}