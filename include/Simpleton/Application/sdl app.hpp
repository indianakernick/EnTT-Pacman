//
//  sdl app.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_application_sdl_app_hpp
#define engine_application_sdl_app_hpp

#include "app.hpp"
#include "../SDL/library.hpp"
#include "../SDL/font library.hpp"

namespace Game {
  template <typename Duration>
  class SDLApp : public App<Duration> {
  public:
    SDLApp() = default;
    virtual ~SDLApp() = default;

    SDL::Library winLib;
    SDL::FontLibrary fontLib;
    SDL::Window window;
    SDL::Renderer renderer;

  protected:
    void initWindow(const SDL::Window::Desc &winDesc, const bool vsync) {
      winLib = SDL::makeLibrary();
      fontLib = SDL::makeFontLibrary();
      window = SDL::makeWindow(winDesc);
      renderer = SDL::makeRenderer(window, vsync);
    }
    void quitWindow() {
      renderer.reset();
      window.reset();
      fontLib.reset();
      winLib.reset();
    }
  };
}

#endif
