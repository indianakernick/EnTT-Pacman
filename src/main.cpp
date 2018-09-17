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
#include <Simpleton/Grid/blit.hpp>
#include <entt/entity/registry.hpp>

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

using PlayerSprite = Grid::Grid<Cell, 3, 3>;

PlayerSprite makePlayer() {
  PlayerSprite player;
  /*
   O
  -|-
  / \
  */
  player(0, 0) = {' ',  Color::white, Color::black};
  player(1, 0) = {'O',  Color::white, Color::black};
  player(2, 0) = {' ',  Color::white, Color::black};
  player(0, 1) = {'-',  Color::white, Color::black};
  player(1, 1) = {'|',  Color::white, Color::black};
  player(2, 1) = {'-',  Color::white, Color::black};
  player(0, 2) = {'/',  Color::white, Color::black};
  player(1, 2) = {' ',  Color::white, Color::black};
  player(2, 2) = {'\\', Color::white, Color::black};
  return player;
}

void run(WINDOW *win) {
  configure(win);
  initColorPairs();
  ScreenBuf screen{getSize(win)};

  Grid::Pos playerPos = screen.size() / 2u;
  PlayerSprite playerSprite = makePlayer();
  while (true) {
  	const int ch = wgetch(win);
  	if (ch == 'q') {
  	  break;
  	} else if (ch == KEY_RESIZE) {
  	  screen.resize(getSize(win));
  	} else if (ch == KEY_UP) {
  	  --playerPos.y;
  	} else if (ch == KEY_RIGHT) {
  	  ++playerPos.x;
  	} else if (ch == KEY_DOWN) {
  	  ++playerPos.y;
  	} else if (ch == KEY_LEFT) {
  	  --playerPos.x;
  	}
  	Grid::blit(screen, playerSprite, playerPos);
  	renderScreen(win, screen);
  	screen.fill(Cell{});
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