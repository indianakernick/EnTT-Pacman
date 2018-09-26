//
//  set_scared_target.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "set_scared_target.hpp"

#include "comp/dir.hpp"
#include "comp/target.hpp"
#include "util/dir2vec.hpp"
#include "comp/position.hpp"
#include "comp/ghost_mode.hpp"

void setScaredTarget(Registry &reg, const MazeState &maze, std::mt19937 &rand) {
  auto view = reg.view<Target, Position, ScaredMode, ActualDir>();
  for (const Entity e : view) {
  	const Grid::Pos pos = view.get<Position>(e).p;
  	const Grid::Dir dir = view.get<ActualDir>(e).d;
  	const Grid::Pos nextPos = pos + toVec(dir);
  	std::uniform_int_distribution<int> dist(0, 3);
  	Grid::Dir candDir = Grid::toDir(dist(rand));
    Grid::Pos candPos = nextPos;

  	for (int i = 0; i != 4; ++i) {
      if (candDir == Grid::opposite(dir)) {
      	candDir = Grid::rotateCW(candDir);
      	continue;
      }

  	  candPos = nextPos + toVec(candDir);
  	  if (maze.outOfRange(candPos)) {
  	  	candDir = Grid::rotateCW(candDir);
  	  	continue;
  	  }

  	  if (maze[candPos] == Tile::wall) {
  	  	candDir = Grid::rotateCW(candDir);
  	  	continue;
  	  }

  	  break;
  	}

  	view.get<Target>(e).p = candPos;
  }
}