//
//  graphics.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "curses.hpp"
#include <Simpleton/Grid/grid.hpp>

enum class Color : uint8_t {
  black   = COLOR_BLACK,
  red     = COLOR_RED,
  green   = COLOR_GREEN,
  yellow  = COLOR_YELLOW,
  blue    = COLOR_BLUE,
  magenta = COLOR_MAGENTA,
  cyan    = COLOR_CYAN,
  white   = COLOR_WHITE
};

constexpr uint8_t color_count = 8;

struct Cell {
  char ch = ' ';
  Color fore = Color::white;
  Color back = Color::black;
};

using ScreenBuf = Grid::Grid<Cell>;

void initColorPairs();
Grid::Pos getWindowSize(WINDOW *);
void configureWindow(WINDOW *);
void renderScreen(WINDOW *, const ScreenBuf &);

#endif