//
//  library.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 3/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_library_hpp
#define engine_sdl_library_hpp

#include "error.hpp"
#include <SDL2/SDL.h>
#include "window.hpp"
#include "renderer.hpp"
#include "../Utils/generic raii.hpp"
#include "../Utils/instance limiter.hpp"

namespace SDL {
  namespace detail {
    void deleteLibrary(bool);
  }

  class Library final : public Utils::ForceSingleton<Library> {
  public:
    UTILS_RAII_CLASS_FULL(Library, bool, initialized, detail::deleteLibrary)
    
  private:
    bool initialized;
  };
  
  Library makeLibrary(Uint32 = SDL_INIT_EVERYTHING);
  
  Window makeWindow(const Window::Desc &);
  Window makeWindow(const char *, int, int);
  Renderer makeRenderer(Window &, bool);
}

#include "library.inl"

#endif
