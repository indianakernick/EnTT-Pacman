//
//  set chase target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "set chase target system.hpp"

#include "dir to vec.hpp"
#include "target component.hpp"
#include "position component.hpp"
#include "actual dir component.hpp"
#include "ghost mode component.hpp"
#include "chase target component.hpp"
#include "home position component.hpp"
#include <Simpleton/Grid/distance.hpp>

void setBlinkyChaseTarget(Registry &reg) {
  auto view = reg.view<Target, ChaseMode, BlinkyChaseTarget>();
  for (const Entity e : view) {
    const Entity player = view.get<BlinkyChaseTarget>(e).player;
    view.get<Target>(e).p = reg.get<Position>(player).p;
  }
}

void setPinkyChaseTarget(Registry &reg) {
  auto view = reg.view<Target, ChaseMode, PinkyChaseTarget>();
  for (const Entity e : view) {
  	const Entity player = view.get<PinkyChaseTarget>(e).player;
  	const Grid::Pos playerPos = reg.get<Position>(player).p;
  	const Grid::Dir playerDir = reg.get<ActualDir>(player).d;
  	view.get<Target>(e).p = playerPos + toVec(playerDir, 4);
  }
}

void setInkyChaseTarget(Registry &reg) {
  auto view = reg.view<Target, ChaseMode, InkyChaseTarget>();
  for (const Entity e : view) {
  	const InkyChaseTarget target = view.get<InkyChaseTarget>(e);
  	const Grid::Pos playerPos = reg.get<Position>(target.player).p;
  	const Grid::Dir playerDir = reg.get<ActualDir>(target.player).d;
  	const Grid::Pos offset = playerPos + toVec(playerDir, 2);
  	const Grid::Pos blinkyPos = reg.get<Position>(target.blinky).p;
  	view.get<Target>(e).p = blinkyPos + (offset - blinkyPos) * 2;
  }
}

void setClydeChaseTarget(Registry &reg) {
  auto view = reg.view<
    Target, Position, ChaseMode, ClydeChaseTarget, HomePosition
  >();
  for (const Entity e : view) {
    const Entity player = view.get<ClydeChaseTarget>(e).player;
  	const Grid::Pos playerPos = reg.get<Position>(player).p;
  	const float dist = Grid::euclid(playerPos, view.get<Position>(e).p);
  	if (dist >= 8.0f) {
  	  view.get<Target>(e).p = playerPos;
  	} else {
  	  view.get<Target>(e).p = view.get<HomePosition>(e).scatter;
  	}
  }
}