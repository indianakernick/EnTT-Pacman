//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "sprites.hpp"
#include "graphics.hpp"
#include <Simpleton/Grid/blit.hpp>

void runGame(WINDOW *win) {
  configureWindow(win);
  initColorPairs();
  ScreenBuf screen{getWindowSize(win)};

  Grid::Pos playerPos = screen.size() / 2u;
  const auto playerSprite = makePlayer();
  const auto rockSprite = makeRock();
  const auto treeSprite = makeTree();
  const auto flowerSprite = makeFlower();
  const auto monsterSprite = makeMonster();

  while (true) {
    int ch;
  	while ((ch = wgetch(win)) != ERR) {
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
  	}
  	Grid::blit(screen, rockSprite, screen.size() / 4u);
  	Grid::blit(screen, treeSprite, screen.size() / 4u * 3u);
  	Grid::blit(screen, flowerSprite, {screen.width() / 4u, screen.height() / 4u * 3u});
  	Grid::blit(screen, monsterSprite, {screen.width() / 4u * 3u, screen.height() / 4u});
    Grid::blit(screen, playerSprite, playerPos);
  	renderScreen(win, screen);
  	screen.fill(Cell{});
  }
  // delwin(win);
}