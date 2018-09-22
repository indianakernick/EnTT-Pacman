//
//  dot render system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "dot render system.hpp"

#include "dimensions.hpp"

void dotRender(SDL::QuadWriter &writer, const MazeState &maze, const Sprite::ID sprite) {
  for (const Grid::Coord y : maze.vert()) {
  	for (const Grid::Coord x : maze.hori()) {
  	  const Tile tile = maze(x, y);
  	  writer.tilePos({x * tileSize, y * tileSize}, {tileSize, tileSize});
  	  if (tile == Tile::dot) {
  	  	writer.tileTex(sprite);
  	  } else if (tile == Tile::energizer) {
  	  	writer.tileTex(sprite + 1);
  	  } else {
  	  	continue;
  	  }
  	  writer.render();
  	}
  }
}