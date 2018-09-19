//
//  movement system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "movement system.hpp"

#include "position component.hpp"
#include "desired dir component.hpp"

void movement(Registry &reg) {
  using ToVec = Grid::ToVec<Grid::Coord, Grid::Dir::RIGHT, Grid::Dir::DOWN>;
  auto view = reg.view<Position, DesiredDir>();
  for (const Entity e : view) {
  	view.get<Position>(e).p += ToVec::conv(view.get<DesiredDir>(e).d);
  }
}