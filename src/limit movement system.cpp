//
//  limit movement system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "limit movement system.hpp"

#include "dir to vec.hpp"
#include "position component.hpp"
#include "desired dir component.hpp"

void limitMovement(Registry &reg) {
  auto view = reg.view<Position, DesiredDir>();
  for (const Entity e : view) {
  	const Grid::Pos pos = view.get<Position>(e).p;
  	Grid::Dir &dir = view.get<DesiredDir>(e).d;
  	const Grid::Pos nextPos = (pos + toVec(dir)) * toVec(dir);
  	if (std::max(nextPos.x, nextPos.y) >= 50) {
  	  dir = Grid::Dir::none;
  	}
  }
}