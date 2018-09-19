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
#include "random movement system.hpp"
#include "clear desired dir system.hpp"
#include <Simpleton/Time/synchronizer.hpp>

void runGame(WINDOW *win) {
  configureWindow(win);
  initColorPairs();

  FrameBuf screen{getWindowSize(win)};
  Registry reg;
  std::mt19937 rand{std::random_device{}()};
  
  const Entity camFocus = makePlayer(reg, {0, 0});
  makeObject(reg, {5, 5}, makeRockSprite());
  makeObject(reg, {24, 2}, makeTreeSprite());
  makeMonster(reg, {-12, -1});
  makeObject(reg, {-25, 3}, makeFlowerSprite());

  bool quit = false;
  while (!quit) {
    Time::Synchronizer sync{std::chrono::nanoseconds{1000'000'000 / 10}};

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

    randomMovement(reg, rand);
  	movement(reg);
  	clearDesiredDir(reg);
  	blitSprites(reg, screen, getCamera(reg, camFocus, screen.size()));

  	renderScreen(win, screen);
  	screen.fill(Cell{});
  }
  // delwin(win);
}