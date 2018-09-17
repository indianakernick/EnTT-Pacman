//
//  sprites.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "graphics.hpp"

template <Grid::Coord Width, Grid::Coord Height>
using Sprite = Grid::Grid<Cell, Width, Height>;

Sprite<3, 3> makePlayer();
Sprite<4, 3> makeRock();
Sprite<4, 4> makeTree();
Sprite<1, 2> makeFlower();
Sprite<4, 4> makeMonster();

#endif