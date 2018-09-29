//
//  set_eaten_target.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "set_eaten_target.hpp"

#include "comp/target.hpp"
#include "comp/ghost_mode.hpp"
#include "comp/home_position.hpp"

void setEatenTarget(Registry &reg) {
  auto view = reg.view<Target, EatenMode, HomePosition>();
  for (const Entity e : view) {
  	view.get<Target>(e).p = view.get<HomePosition>(e).home;
  }
}