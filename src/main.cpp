//
//  main.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <iostream>
#include <exception>
#include <SDL_main.h>
#include "core/app.hpp"

extern "C" int main(int, char *[]) {
  try {
    Application app;
    app.run();
  } catch (std::exception &e) {
    // The only exceptions we should get are from SDL
    std::cout << e.what() << '\n';
    return 1;
  }
  return 0;
}
