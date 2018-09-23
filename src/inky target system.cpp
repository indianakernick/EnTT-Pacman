//
//  inky target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "inky target system.hpp"

#include "dir to vec.hpp"
#include "target component.hpp"
#include "position component.hpp"
#include "actual dir component.hpp"
#include "inky target component.hpp"

void inkyTarget(Registry &reg) {
  auto view = reg.view<Target, InkyTarget>();
  for (const Entity e : view) {
  	const InkyTarget target = view.get<InkyTarget>(e);
  	const Grid::Pos playerPos = reg.get<Position>(target.player).p;
  	const Grid::Dir playerDir = reg.get<ActualDir>(target.player).d;
  	const Grid::Pos offset = playerPos + toVec(playerDir, 2);
  	const Grid::Pos blinkyPos = reg.get<Position>(target.blinky).p;
  	view.get<Target>(e).p = blinkyPos + (offset - blinkyPos) * 2;
  }
}