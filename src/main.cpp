//
//  main.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "curses.hpp"
#include <random>
#include <cassert>
#include <Simpleton/Grid/grid.hpp>
#include <entt/entity/registry.hpp>

enum class Color : uint8_t {
  black,
  red,
  green,
  yellow,
  blue,
  magenta,
  cyan,
  white,

  count_
};

constexpr uint8_t color_count = static_cast<uint8_t>(Color::count_);

uint8_t colorPair(const uint8_t fore, const uint8_t back) {
  assert(0 <= fore && fore < color_count);
  assert(0 <= back && back < color_count);
  return fore * color_count + back + 1;
}

void initColorPairs() {
  for (uint8_t f = 0; f != color_count; ++f) {
  	for (uint8_t b = 0; b != color_count; ++b) {
  	  if (init_pair(colorPair(f, b), f, b) == ERR) {
        throw std::runtime_error("Failed to initialize colors");
  	  }
  	}
  }
}

struct Cell {
  char ch = ' ';
  Color fore = Color::white;
  Color back = Color::black;
};

using ScreenBuf = Grid::Grid<Cell>;

Grid::Pos getSize(WINDOW *win) {
  int y;
  int x;
  getmaxyx(win, y, x);
  return {static_cast<Grid::Coord>(x), static_cast<Grid::Coord>(y)};
}

void renderCell(WINDOW *win, const Cell cell) {
  const short pairIndex = colorPair(
    static_cast<uint8_t>(cell.fore), 
    static_cast<uint8_t>(cell.back)
  );
  wattron(win, COLOR_PAIR(pairIndex));
  waddch(win, cell.ch);
}

void renderScreen(WINDOW *win, const ScreenBuf &screen) {
  wmove(win, 0, 0);
  for (const Grid::Coord y : screen.vert()) {
  	for (const Grid::Coord x : screen.hori()) {
  	  renderCell(win, screen(x, y));
  	}
  }
  wrefresh(win);
}

void configure(WINDOW *win) {
  if (curs_set(0) == ERR) {
    throw std::runtime_error("Failed to hide the cursor");
  }
  if (noecho() == ERR) {
  	throw std::runtime_error("Failed to disable input echoing");
  }
  if (start_color() == ERR) {
  	throw std::runtime_error("Failed to enable colors");
  }
  if (nodelay(win, TRUE) == ERR) {
  	throw std::runtime_error("Failed to set nodelay mode");
  }
  if (keypad(win, TRUE) == ERR) {
  	throw std::runtime_error("Failed to enable handling of arrow keys");
  }
}

void run(WINDOW *win) {
  configure(win);
  initColorPairs();
  ScreenBuf screen{getSize(win)};

  std::mt19937 gen;
  std::uniform_int_distribution<Grid::Coord> xdist(0, screen.width() - 1);
  std::uniform_int_distribution<Grid::Coord> ydist(0, screen.height() - 1);
  std::uniform_int_distribution<int> colordist(1, color_count - 1);

  while (true) {
  	const int ch = wgetch(win);
  	if (ch != ERR) {
  	  if (ch == 'q') {
  	  	break;
  	  }
  	  Cell &cell = screen(xdist(gen), ydist(gen));
  	  cell.ch = ch;
  	  cell.fore = static_cast<Color>(colordist(gen));
  	}
  	renderScreen(win, screen);
  }
  // delwin(win);
}

int main() {
  WINDOW *win = initscr();
  try {
    run(win);
  } catch (std::exception &e) {
  	endwin();
  	printf("%s\n", e.what());
  	return 1;
  }
  endwin();
  return 0;
}