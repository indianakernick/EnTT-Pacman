//
//  app.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 17/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "app.hpp"

#include <SDL.h>
#include <iostream>
#include "game.hpp"
#include "constants.hpp"
#include "util/frame_cap.hpp"
#include "util/sdl_check.hpp"
#include "util/sdl_delete.hpp"
#include "util/sdl_load_texture.hpp"

namespace {

int getScaleFactor() {
  // Make the largest window possible with an integer scale factor
  SDL_Rect bounds;
  #if SDL_VERSION_ATLEAST(2, 0, 5)
  SDL_CHECK(SDL_GetDisplayUsableBounds(0, &bounds));
  #else
  #warning SDL 2.0.5 or later is recommended
  SDL_CHECK(SDL_GetDisplayBounds(0, &bounds));
  #endif
  const int scaleX = bounds.w / tilesPx.x;
  const int scaleY = bounds.h / tilesPx.y;
  return std::max(1, std::min(scaleX, scaleY));
}

}

Application::Application() {
  SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));
}

Application::~Application() {
  SDL_Quit();
}

void Application::run() {
  const int scaleFactor = getScaleFactor();
  std::cout << "Using scale factor: " << scaleFactor << '\n';

  SDL::Window window{SDL_CHECK(SDL_CreateWindow(
    "Pacman",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    tilesPx.x * scaleFactor, tilesPx.y * scaleFactor,
    SDL_WINDOW_SHOWN
  ))};

  SDL::Renderer renderer{SDL_CHECK(SDL_CreateRenderer(
    window.get(),
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  ))};
  SDL_CHECK(SDL_RenderSetLogicalSize(renderer.get(), tilesPx.x, tilesPx.y));

  SDL::Texture maze = SDL::loadTexture(renderer.get(), animera::getTextureInfo());
  SDL::QuadWriter writer{renderer.get(), maze.get()};
  Game game;
  game.init();

  int frame = 0;
  bool quit = false;
  while (!quit) {
    FrameCap sync{fps};

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
        break;
      } else if (e.type == SDL_KEYDOWN) {
        game.input(e.key.keysym.scancode);
      }
    }

    // Game::logic is called once for each tile
    // Game::render is called for each pixel between tiles
    if (frame % tileSize == 0) {
      if (!game.logic()) {
        quit = true;
      }
    }

    SDL_CHECK(SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255));
    SDL_CHECK(SDL_RenderClear(renderer.get()));
    game.render(writer, frame % tileSize);
    ++frame;
    SDL_RenderPresent(renderer.get());
  }
}
