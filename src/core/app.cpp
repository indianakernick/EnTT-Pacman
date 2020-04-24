//
//  app.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "app.hpp"

#include <SDL.h>
#include "game.hpp"
#include "constants.hpp"
#include "../util/sdl_check.hpp"
#include "../util/sdl_delete.hpp"
#include "../util/sdl_load_texture.hpp"
#include <Simpleton/Time/synchronizer.hpp>

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
  const glm::ivec2 scale = {bounds.w / tilesPx.x, bounds.h / tilesPx.y};
  return std::max(1, std::min(scale.x, scale.y));
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

  SDL::Texture maze = SDL::loadTexture(renderer.get(), "sprites.png");

  Sprite::Sheet sheet = Sprite::makeSheetFromFile("sprites.atlas");
  SDL::QuadWriter writer{renderer.get(), maze.get(), sheet};
  Game game;

  game.init(sheet);

  int frame = 0;
  bool quit = false;
  while (!quit) {
    Time::Synchronizer sync{Time::sync_fps, fps};

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
