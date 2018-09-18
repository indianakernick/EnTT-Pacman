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
#include <Simpleton/Grid/blit.hpp>

struct Cell {
  char ch = ' ';
  ColIdx color = color_sys(Color::white);
};

using ScreenBuf = Grid::Grid<Cell>;

template <Grid::Coord Width, Grid::Coord Height>
using Sprite = Grid::Grid<Cell, Width, Height>;

template <Grid::Coord Width, Grid::Coord Height>
void blit(ScreenBuf &buf, const Sprite<Width, Height> &sprite, const Grid::Pos pos) {
  const auto copy = [] (Cell &dst, const Cell &src) {
  	if (src.ch != ' ') {
  	  dst = src;
  	}
  };
  Grid::blit(buf, sprite, copy, pos);
}

#endif