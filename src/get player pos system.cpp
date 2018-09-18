//
//  get player pos system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "get player pos system.hpp"

#include <cassert>
#include "player component.hpp"
#include "position component.hpp"

Grid::Pos getPlayerPos(Registry &reg) {
  const auto view = reg.view<Player, Position>();
  for (const Entity e : view) {
  	return view.get<Position>(e).p;
  }
  assert(false);
  return {};
}