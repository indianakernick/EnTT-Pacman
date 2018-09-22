//
//  movement system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "movement system.hpp"

#include "dir to vec.hpp"
#include "position component.hpp"
#include "actual dir component.hpp"

void movement(Registry &reg) {
  auto view = reg.view<Position, ActualDir>();
  for (const Entity e : view) {
    Grid::Pos &pos = view.get<Position>(e).p;
    const Grid::Dir dir = view.get<ActualDir>(e).d;
  	pos += toVec(dir);

    // the tunnel
    if (pos.y == 10) {
      if (pos.x <= -1 && dir == Grid::Dir::left) {
  	    pos.x = 19;
  	  } else if (pos.x >= 19 && dir == Grid::Dir::right) {
  	    pos.x = -1;
  	  }
  	}
  }
}