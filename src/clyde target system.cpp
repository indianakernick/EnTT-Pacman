//
//  clyde target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "clyde target system.hpp"

#include "target component.hpp"
#include "position component.hpp"
#include "ghost mode component.hpp"
#include "clyde target component.hpp"
#include <Simpleton/Grid/distance.hpp>
#include "home position component.hpp"

void clydeTarget(Registry &reg) {
  auto view = reg.view<
    Target, Position, ChaseMode, ClydeTarget, HomePosition
  >();
  for (const Entity e : view) {
    const Entity player = view.get<ClydeTarget>(e).player;
  	const Grid::Pos playerPos = reg.get<Position>(player).p;
  	const float dist = Grid::euclid(playerPos, view.get<Position>(e).p);
  	if (dist >= 8.0f) {
  	  view.get<Target>(e).p = playerPos;
  	} else {
  	  view.get<Target>(e).p = view.get<HomePosition>(e).scatter;
  	}
  }
}