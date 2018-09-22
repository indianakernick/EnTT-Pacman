//
//  player render system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "player render system.hpp"

#include "dimensions.hpp"
#include "dir to vec.hpp"
#include "player component.hpp"
#include "position component.hpp"
#include "sprite id component.hpp"
#include "actual dir component.hpp"
#include "desired dir component.hpp"

void playerRender(Registry &reg, SDL::QuadWriter &writer, const int frame) {
  const auto view = reg.view<Player, Position, SpriteID, ActualDir, DesiredDir>();
  for (const Entity e : view) {
    const Grid::Pos pos = view.get<Position>(e).p * tileSize;
    const Grid::Dir actualDir = view.get<ActualDir>(e).d;
    const double angle = Grid::toNum(view.get<DesiredDir>(e).d, 90.0);
  	writer.tilePos(pos + toVec(actualDir, frame), glm::ivec2(tileSize), angle);
  	writer.tileTex(view.get<SpriteID>(e).id + frame);
  	writer.render();
  }
}