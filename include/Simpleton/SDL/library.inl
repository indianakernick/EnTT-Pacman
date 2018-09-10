//
//  library.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 3/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "../Utils/bool enable.hpp"

inline void SDL::detail::deleteLibrary(const bool initialized) {
  if (initialized) {
    SDL_Quit();
  }
}

inline SDL::Library SDL::makeLibrary(const Uint32 flags) {
  CHECK_SDL_ERROR(SDL_Init(flags));
  return SDL::Library(true);
}

inline SDL::Window SDL::makeWindow(const Window::Desc &desc) {
  return Window(CHECK_SDL_NULL(SDL_CreateWindow(
    desc.title.c_str(),
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    desc.size.x, desc.size.y,
    SDL_WINDOW_SHOWN |
    Utils::boolEnable(desc.resizable, SDL_WINDOW_RESIZABLE) |
    Utils::boolEnable(desc.openGL, SDL_WINDOW_OPENGL)
  )));
}

inline SDL::Window SDL::makeWindow(const char *title, const int w, const int h) {
  return Window(CHECK_SDL_NULL(SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    w, h,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
  )));
}

inline SDL::Renderer SDL::makeRenderer(Window &window, const bool vsync) {
  return Renderer(CHECK_SDL_NULL(SDL_CreateRenderer(
    window.get(),
    -1,
    SDL_RENDERER_ACCELERATED |
    Utils::boolEnable(vsync, SDL_RENDERER_PRESENTVSYNC)
  )));
}
