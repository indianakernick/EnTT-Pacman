//
//  main.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <iostream>
#include <exception>
#include "core/app.hpp"
#include <SDL2/SDL_main.h>
#include <Simpleton/SDL/library.hpp>

extern "C" int main(int, char *[]) {
  SDL::Library lib = SDL::makeLibrary(SDL_INIT_VIDEO);
  try {
    runGame();
  } catch (std::exception &e) {
    // The only exceptions we should get are from SDL
    std::cout << e.what() << '\n';
  	return 1;
  }
  return 0;
}