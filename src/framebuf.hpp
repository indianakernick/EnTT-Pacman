//
//  framebuf.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef FRAMEBUF_HPP
#define FRAMEBUF_HPP

#include "color.hpp"
#include <Simpleton/Grid/grid.hpp>

struct Cell {
  char ch = ' ';
  ColIdx color = color_sys(Color::white);
};

using FrameBuf = Grid::Grid<Cell>;

void blit(FrameBuf &, const FrameBuf &, Grid::Pos);

#endif