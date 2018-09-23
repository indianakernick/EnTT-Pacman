//
//  blinky target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "blinky target system.hpp"

#include "target component.hpp"
#include "position component.hpp"
#include "ghost mode component.hpp"
#include "blinky target component.hpp"

void blinkyTarget(Registry &reg) {
  auto view = reg.view<Target, ChaseMode, BlinkyTarget>();
  for (const Entity e : view) {
    const Entity player = view.get<BlinkyTarget>(e).player;
	view.get<Target>(e).p = reg.get<Position>(player).p;
  }
}