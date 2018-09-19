//
//  player input system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "player input system.hpp"

#include <cassert>
#include "curses.hpp"
#include "player component.hpp"
#include "desired dir component.hpp"

Consumed playerInput(Registry &reg, const int key) {
  auto view = reg.view<Player, DesiredDir>();
  for (const Entity e : view) {
    if (key == KEY_UP) {
      view.get<DesiredDir>(e).d = Grid::Dir::up;
  	} else if (key == KEY_RIGHT) {
      view.get<DesiredDir>(e).d = Grid::Dir::right;
    } else if (key == KEY_DOWN) {
      view.get<DesiredDir>(e).d = Grid::Dir::down;
  	} else if (key == KEY_LEFT) {
      view.get<DesiredDir>(e).d = Grid::Dir::left;
   	} else {
   	  return Consumed::no;
   	}
   	return Consumed::yes;
  }
  assert(false);
  return Consumed::no;
}