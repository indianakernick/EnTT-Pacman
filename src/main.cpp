//
//  main.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <iostream>
#include <exception>
#include "application.hpp"
#include <Simpleton/SDL/library.hpp>

int main() {
  SDL::Library lib = SDL::makeLibrary(SDL_INIT_VIDEO);
  try {
    runGame();
  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
  	return 1;
  }
  return 0;
}