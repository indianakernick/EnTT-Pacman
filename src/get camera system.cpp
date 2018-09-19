//
//  get camera system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "get camera system.hpp"

#include "position component.hpp"

Grid::Pos getCamera(Registry &reg, const Entity focus, const Grid::Pos screenSize) {
  return screenSize / 2 - reg.get<Position>(focus).p;
}