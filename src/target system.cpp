//
//  target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "target system.hpp"

#include <algorithm>
#include "dir to vec.hpp"
#include "target component.hpp"
#include "position component.hpp"
#include "actual dir component.hpp"
#include "desired dir component.hpp"
#include <Simpleton/Grid/distance.hpp>

// Pacman doesn't use A*

void target(Registry &reg, const MazeState &maze) {
  constexpr float inf = 1e10f;
  auto view = reg.view<Target, Position, ActualDir, DesiredDir>();
  for (const Entity e : view) {
  	const Grid::Pos targetPos = view.get<Target>(e).p;
  	// the position we are currently moving from
  	const Grid::Pos pos = view.get<Position>(e).p;
  	// the direction we are currently moving in
  	const Grid::Dir dir = view.get<ActualDir>(e).d;
  	// the position we are currently moving to
  	const Grid::Pos nextPos = pos + toVec(dir);
  	// distance from the 4 candiate directions to the target
    float targetDist[4] = {inf, inf, inf, inf};
  	for (const Grid::Dir candDir : Grid::dir_range) {
      // can't go back the way we came
  	  if (candDir == Grid::opposite(dir)) {
  	  	continue;
  	  }

      // gotta stay in the maze
  	  const Grid::Pos candPos = nextPos + toVec(candDir);
  	  if (maze.outOfRange(candPos)) {
  	  	continue;
  	  }

      // can't go through walls
  	  const Tile candTile = maze[candPos];
  	  if (candTile == Tile::wall) {
  	  	continue;
  	  }

  	  targetDist[Grid::toNum<size_t>(candDir)] = Grid::euclid(candPos, targetPos);
  	}

  	float *smallestDist = std::min_element(targetDist, targetDist + 4);
  	if (smallestDist == targetDist + 4 || *smallestDist == inf) {
  	  view.get<DesiredDir>(e).d = dir;
  	  continue;
  	}

  	view.get<DesiredDir>(e).d = Grid::toDir(smallestDist - targetDist);
  }
}