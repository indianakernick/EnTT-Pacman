//
//  factories.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "factories.hpp"

#include "sprite id component.hpp"
#include "maze sprite component.hpp"

Entity makeMaze(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<SpriteID>(e, sheet.getIDfromName("maze"));
  reg.assign<MazeSprite>(e);
  return e;
}