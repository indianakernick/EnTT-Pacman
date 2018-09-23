//
//  maze render system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "maze render system.hpp"

#include "dimensions.hpp"
#include "maze sprite component.hpp"

void mazeRender(Registry &reg, SDL::QuadWriter &writer) {
  const auto view = reg.view<MazeSprite>();
  for (const Entity e : view) {
  	writer.tilePos({0, 0}, tiles * tileSize);
  	writer.tileTex(view.get(e).id);
  	writer.render();
  }
}