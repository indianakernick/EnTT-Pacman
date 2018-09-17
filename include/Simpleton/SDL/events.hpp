//
//  events.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_events_hpp
#define engine_sdl_events_hpp

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>

namespace SDL {
  bool keyDown(const SDL_Event &, SDL_Scancode);
  bool keyUp(const SDL_Event &, SDL_Scancode);
  bool keyDown(const SDL_Event &);
  bool keyUp(const SDL_Event &);
  SDL_Scancode keyCode(const SDL_KeyboardEvent &);
}

#include "events.inl"

#endif
