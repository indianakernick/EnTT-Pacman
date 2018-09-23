//
//  scared target system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "scared target system.hpp"

#include "dir to vec.hpp"
#include "target component.hpp"
#include "position component.hpp"
#include "ghost mode component.hpp"
#include "actual dir component.hpp"

void scaredTarget(Registry &reg, const MazeState &maze, std::mt19937 &rand) {
  auto view = reg.view<Target, Position, ScaredMode, ActualDir>();
  for (const Entity e : view) {
  	const Grid::Pos pos = view.get<Position>(e).p;
  	const Grid::Dir dir = view.get<ActualDir>(e).d;
  	const Grid::Pos nextPos = pos + toVec(dir);
  	std::uniform_int_distribution<Grid::DirType> dist(0, 3);
  	Grid::Dir candDir = Grid::toDir(dist(rand));
    Grid::Pos candPos;

  	while (true) {
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