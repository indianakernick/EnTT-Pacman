//
//  render.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "render.hpp"

#include "comp/dir.hpp"
#include "comp/sprite.hpp"
#include "util/dir2vec.hpp"
#include "comp/position.hpp"
#include "core/constants.hpp"
#include "core/constants.hpp"
#include "comp/ghost_mode.hpp"

void playerRender(Registry &reg, SDL::QuadWriter &writer, const int frame) {
  const auto view = reg.view<Position, ActualDir, DesiredDir, PlayerSprite>();
  for (const Entity e : view) {
    const Grid::Pos pos = view.get<Position>(e).p * tileSize;
    const Grid::Dir actualDir = view.get<ActualDir>(e).d;
    const double angle = Grid::toNum(view.get<DesiredDir>(e).d, 90.0);
  	writer.tilePos(pos + toVec(actualDir, frame), glm::ivec2(tileSize), angle);
  	writer.tileTex(view.get<PlayerSprite>(e).id + frame);
  	writer.render();
  }
}

void ghostRender(Registry &reg, SDL::QuadWriter &writer, const int frame) {
  const auto view = reg.view<Position, ActualDir, GhostSprite>();
  for (const Entity e : view) {
  	const Grid::Pos pos = view.get<Position>(e).p * tileSize;
  	const Grid::Dir actualDir = view.get<ActualDir>(e).d;
  	writer.tilePos(pos + toVec(actualDir, frame), glm::ivec2(tileSize));
  	const Sprite::ID dirOffset = (
  	  actualDir == Grid::Dir::none ? 0 : Grid::toNum<Sprite::ID>(actualDir)
  	);
  	const GhostSprite sprite = view.get<GhostSprite>(e);
  	if (reg.has<ChaseMode>(e) || reg.has<ScatterMode>(e)) {
  	  writer.tileTex(sprite.id + dirOffset);
  	} else if (reg.has<ScaredMode>(e)) {
  	  const int scaredTimer = reg.get<ScaredMode>(e).timer;
  	  const int flash = (
  	    scaredTimer <= ghostScaredFlashTime ? (frame / ghostScaredFlashRate) % 2 : 0
  	  );
  	  writer.tileTex(sprite.scared + flash);
  	} else if (reg.has<EatenMode>(e)) {
  	  writer.tileTex(sprite.eyes + dirOffset);
  	}
  	writer.render();
  }
}

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

void mazeRender(Registry &reg, SDL::QuadWriter &writer) {
  const auto view = reg.view<MazeSprite>();
  for (const Entity e : view) {
  	writer.tilePos({0, 0}, tiles * tileSize);
  	writer.tileTex(view.get(e).id);
  	writer.render();
  }
}

void winloseRender(SDL::QuadWriter &writer, const Sprite::ID sprite) {
  writer.tilePos({0, 0}, tiles * tileSize);
  writer.tileTex(sprite);
  writer.render();
}