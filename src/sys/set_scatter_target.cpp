//
//  set_scatter_target.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "set_scatter_target.hpp"

#include "comp/target.hpp"
#include "comp/ghost_mode.hpp"
#include "comp/home_position.hpp"

void setScatterTarget(Registry &reg) {
  auto view = reg.view<Target, ScatterMode, HomePosition>();
  for (const Entity e : view) {
  	view.get<Target>(e).p = view.get<HomePosition>(e).scatter;
  }
}