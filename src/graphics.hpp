//
//  graphics.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "color.hpp"
#include "curses.hpp"
#include <Simpleton/Grid/grid.hpp>

struct Cell {
  char ch = ' ';
  ColIdx color = color_sys(Color::white);
};

using ScreenBuf = Grid::Grid<Cell>;

void initColorPairs();
Grid::Pos getWindowSize(WINDOW *);
void configureWindow(WINDOW *);
void renderScreen(WINDOW *, const ScreenBuf &);

#endif