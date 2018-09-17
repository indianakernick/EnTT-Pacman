//
//  main.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"
#include <exception>

int main() {
  WINDOW *win = initscr();
  try {
    runGame(win);
  } catch (std::exception &e) {
  	endwin();
  	printf("%s\n", e.what());
  	return 1;
  }
  endwin();
  return 0;
}