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
#include "blinky target component.hpp"

void blinkyTarget(Registry &reg) {
  auto view = reg.view<Target, BlinkyTarget>();
  for (const Entity e : view) {
  	view.get<Target>(e).p = reg.get<Position>(view.get<BlinkyTarget>(e).player).p;
  }
}