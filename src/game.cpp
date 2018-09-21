//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "registry.hpp"
#include <Simpleton/SDL/library.hpp>
#include <Simpleton/Time/synchronizer.hpp>

SDL::Window::Desc getWinDesc() {
  SDL::Window::Desc desc;
  desc.title = "Pacman";
  desc.size = {19*8*4, 22*8*4};
  desc.resizable = false;
  desc.openGL = false;
  return desc;
}

void runGame() {
  SDL::Window window = SDL::makeWindow(getWinDesc());
  Registry reg;

  bool quit = false;
  while (!quit) {
    Time::Synchronizer sync{std::chrono::nanoseconds{1000'000'000 / 10}};

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
      	quit = true;
      	break;
      }
    }
  }
}