//
//  set scatter target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "set scatter target system.hpp"

#include "target component.hpp"
#include "ghost mode component.hpp"
#include "home position component.hpp"

void setScatterTarget(Registry &reg) {
  auto view = reg.view<Target, ScatterMode, HomePosition>();
  for (const Entity e : view) {
  	view.get<Target>(e).p = view.get<HomePosition>(e).scatter;
  }
}