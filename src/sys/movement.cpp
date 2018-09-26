//
//  movement.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "movement.hpp"

#include "comp/dir.hpp"
#include "util/dir2vec.hpp"
#include "comp/position.hpp"

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

void wallCollide(Registry &reg, const MazeState &maze) {
  auto view = reg.view<Position, ActualDir, DesiredDir>();
  for (const Entity e : view) {
    const Grid::Dir desiredDir = view.get<DesiredDir>(e).d;
    const Grid::Pos pos = view.get<Position>(e).p;
  	const Grid::Pos desiredPos = pos + toVec(desiredDir);
  	Grid::Dir &actualDir = view.get<ActualDir>(e).d;
  	if (maze.outOfRange(desiredPos)) {
  	  // the tunnel is the only place where empty space meets the edge of the map
  	  // the movement system will handle this
  	  actualDir = desiredDir;
  	  continue;
  	}

  	const Tile desiredTile = maze[desiredPos];
  	if (desiredTile != Tile::wall) {
  	  actualDir = desiredDir;
  	  continue;
  	}

    // desired direction is no good
    // maybe we can keep going that same way we did last tick
    const Grid::Pos actualPos = pos + toVec(actualDir);
    if (maze.outOfRange(actualPos)) {
      // not sure how this could happen
      assert(false);
    }

    const Tile actualTile = maze[actualPos];
    if (actualTile != Tile::wall) {
      continue;
    }

  	actualDir = Grid::Dir::none;
  }
}