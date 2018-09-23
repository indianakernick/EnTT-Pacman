//
//  sdl error.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_error_hpp
#define engine_sdl_error_hpp

#include <stdexcept>
#include <SDL2/SDL_error.h>

namespace SDL {
  class Error final : public std::runtime_error {
  public:
    inline Error()
      : std::runtime_error(SDL_GetError()) {}
  };
  
  namespace detail {
    template <typename Ptr>
    Ptr checkSDLNull(const Ptr ptr) {
      if (ptr == nullptr) throw Error();
      return ptr;
    }
  }
}

#ifdef DISABLE_SDL_ERROR_CHECK

#define CHECK_SDL_ERROR(SDL_FUN_CALL) (SDL_FUN_CALL)
#define CHECK_SDL_NULL(SDL_FUN_CALL) (SDL_FUN_CALL)

#else

#define CHECK_SDL_ERROR(SDL_FUN_CALL) ((SDL_FUN_CALL) != 0 ? throw SDL::Error() : void())
#define CHECK_SDL_NULL(SDL_FUN_CALL) SDL::detail::checkSDLNull(SDL_FUN_CALL)

#endif

#endif
