//
//  pinky target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "pinky target system.hpp"

#include "dir to vec.hpp"
#include "target component.hpp"
#include "position component.hpp"
#include "actual dir component.hpp"
#include "pinky target component.hpp"

void pinkyTarget(Registry &reg) {
  auto view = reg.view<Target, PinkyTarget>();
  for (const Entity e : view) {
  	const Entity player = view.get<PinkyTarget>(e).player;
  	const Grid::Pos playerPos = reg.get<Position>(player).p;
  	const Grid::Dir playerDir = reg.get<ActualDir>(player).d;
  	view.get<Target>(e).p = playerPos + toVec(playerDir, 4);
  }
}