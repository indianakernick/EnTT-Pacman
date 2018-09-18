//
//  move player system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "move player system.hpp"

#include "player component.hpp"
#include "position component.hpp"

void movePlayer(Registry &reg, const Grid::Dir dir) {
  using ToVec = Grid::ToVec<Grid::Coord, Grid::Dir::RIGHT, Grid::Dir::DOWN>;
  auto view = reg.view<Player, Position>();
  for (const Entity e : view) {
  	view.get<Position>(e).p += ToVec::conv(dir);
  }
}