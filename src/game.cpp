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
#include "factories.hpp"
#include "movement system.hpp"
#include "get camera system.hpp"
#include "player input system.hpp"
#include "blit sprites system.hpp"
#include "clear desired dir system.hpp"
#include <Simpleton/Time/synchronizer.hpp>

void runGame(WINDOW *win) {
  configureWindow(win);
  initColorPairs();

  FrameBuf screen{getWindowSize(win)};
  Registry reg;
  const Entity camFocus = makePlayer(reg, {0, 0});
  makeObject(reg, {5, 5}, makeRockSprite());
  makeObject(reg, {24, 2}, makeTreeSprite());
  makeObject(reg, {-12, -1}, makeMonsterSprite());
  makeObject(reg, {-25, 3}, makeFlowerSprite());

  bool quit = false;
  while (!quit) {
    Time::Synchronizer sync{std::chrono::nanoseconds{1'000'000'000 / 20}};

    int ch;
  	while ((ch = wgetch(win)) != ERR) {
      if (ch == 'q') {
  	    quit = true;
  	    break;
  	  } else if (ch == KEY_RESIZE) {
  	    screen.resize(getWindowSize(win));
  	  } else {
  	  	playerInput(reg, ch);
  	  }
  	}

  	movement(reg);
  	clearDesiredDir(reg);
  	blitSprites(reg, screen, getCamera(reg, camFocus, screen.size()));

  	renderScreen(win, screen);
  	screen.fill(Cell{});
  }
  // delwin(win);
}