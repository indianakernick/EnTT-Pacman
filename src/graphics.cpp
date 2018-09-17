//
//  graphics.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "graphics.hpp"

#include <cassert>

namespace {

uint8_t colorPair(const uint8_t fore, const uint8_t back) {
  assert(0 <= fore && fore < color_count);
  assert(0 <= back && back < color_count);
  return fore * color_count + back + 1;
}

int textAttribute(const Attr attr) {
  switch (attr) {
  	case Attr::normal:
  	  return A_NORMAL;
  	case Attr::dim:
  	  return A_DIM;
  	case Attr::bold:
  	  return A_BOLD;
  	default:
  	  assert(false);
  }
}

void renderCell(WINDOW *win, const Cell cell) {
  const uint8_t pairIndex = colorPair(
    static_cast<uint8_t>(cell.fore), 
    static_cast<uint8_t>(cell.back)
  );
  wattrset(win, COLOR_PAIR(pairIndex) | textAttribute(cell.attr));
  waddch(win, cell.ch);
}

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
  // wgetch is non-blocking and returns ERR if there is no character available
  if (nodelay(win, TRUE) == ERR) {
  	throw std::runtime_error("Failed to set nodelay mode");
  }
  // wgetch will return KEY_RIGHT if the user presses the right arrow key
  if (keypad(win, TRUE) == ERR) {
  	throw std::runtime_error("Failed to enable handling of arrow keys");
  }
}

void renderScreen(WINDOW *win, const ScreenBuf &screen) {
  wmove(win, 0, 0);
  for (const Grid::Coord y : screen.vert()) {
  	for (const Grid::Coord x : screen.hori()) {
  	  renderCell(win, screen(x, y));
  	}
  }
  // Imagine this is just SDL_GL_SwapWindow
  wrefresh(win);
}