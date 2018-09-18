//
//  graphics.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "graphics.hpp"

namespace {

void renderCell(WINDOW *win, const Cell cell) {
  wattrset(win, COLOR_PAIR(cell.color));
  waddch(win, cell.ch);
}

}

void initColorPairs() {
  for (int c = 0; c != 256; ++c) {
  	if (init_pair(c, c, -1) == ERR) {
      throw std::runtime_error("Failed to initialize colors");
  	}
  }
}

Grid::Pos getWindowSize(WINDOW *win) {
  assert(win);
  Grid::Pos pos;
  pos.x = getmaxx(win);
  pos.y = getmaxy(win);
  return pos;
}

void configureWindow(WINDOW *win) {
  // Cursor is invisible
  if (curs_set(0) == ERR) {
    throw std::runtime_error("Failed to hide the cursor");
  }
  // The keys that are pressed do not appear on the screen
  if (noecho() == ERR) {
  	throw std::runtime_error("Failed to disable input echoing");
  }
  // Colors are available
  if (start_color() == ERR) {
  	throw std::runtime_error("Failed to enable colors");
  }
  if (COLORS < 256) {
  	throw std::runtime_error("Terminal not in 256 color mode");
  }
  if (COLOR_PAIRS < 256) {
  	throw std::runtime_error("Not enough color pairs available");
  }
  // wgetch is non-blocking and returns ERR if there is no character available
  if (nodelay(win, TRUE) == ERR) {
  	throw std::runtime_error("Failed to set nodelay mode");
  }
  // wgetch will return KEY_RIGHT if the user presses the right arrow key
  if (keypad(win, TRUE) == ERR) {
  	throw std::runtime_error("Failed to enable handling of arrow keys");
  }
  // -1 is the default background or foreground color
  if (use_default_colors() == ERR) {
  	throw std::runtime_error("Failed to enable default colors");
  }
}

void renderScreen(WINDOW *win, const FrameBuf &screen) {
  wmove(win, 0, 0);
  for (const Grid::Coord y : screen.vert()) {
  	for (const Grid::Coord x : screen.hori()) {
  	  renderCell(win, screen(x, y));
  	}
  }
  // Imagine this is just SDL_GL_SwapWindow
  wrefresh(win);
}