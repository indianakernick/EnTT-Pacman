//
//  ghost render system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "ghost render system.hpp"

#include "dimensions.hpp"
#include "dir to vec.hpp"
#include "position component.hpp"
#include "actual dir component.hpp"
#include "ghost sprite component.hpp"

void ghostRender(Registry &reg, SDL::QuadWriter &writer, const int frame) {
  const auto view = reg.view<Position, ActualDir, GhostSprite>();
  for (const Entity e : view) {
  	const Grid::Pos pos = view.get<Position>(e).p * tileSize;
  	const Grid::Dir actualDir = view.get<ActualDir>(e).d;
  	writer.tilePos(pos + toVec(actualDir, frame), glm::ivec2(tileSize));
  	const Sprite::ID tex = actualDir == Grid::Dir::none ? 0 : Grid::toNum<Sprite::ID>(actualDir);
  	writer.tileTex(view.get<GhostSprite>(e).id + tex);
  	writer.render();
  }
}