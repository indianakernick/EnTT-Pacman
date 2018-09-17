//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "graphics.hpp"
#include <Simpleton/Grid/blit.hpp>

namespace {

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

}

void runGame(WINDOW *win) {
  configureWindow(win);
  initColorPairs();
  ScreenBuf screen{getWindowSize(win)};

  Grid::Pos playerPos = screen.size() / 2u;
  PlayerSprite playerSprite = makePlayer();
  while (true) {
  	const int ch = wgetch(win);
  	if (ch == 'q') {
  	  break;
  	} else if (ch == KEY_RESIZE) {
  	  screen.resize(getWindowSize(win));
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