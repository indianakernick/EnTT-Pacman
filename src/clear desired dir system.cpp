//
//  clear desired dir system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "clear desired dir system.hpp"

#include "desired dir component.hpp"

void clearDesiredDir(Registry &reg) {
  auto view = reg.view<DesiredDir>();
  for (const Entity e : view) {
  	view.get(e).d = Grid::Dir::none;
  }
}