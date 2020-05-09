//
//  sdl_check.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/4/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#ifndef UTIL_SDL_CHECK_HPP
#define UTIL_SDL_CHECK_HPP

#include <stdexcept>
#include <SDL_error.h>

namespace SDL {

[[noreturn]] inline void raise() {
  const char *error = SDL_GetError();
  throw std::runtime_error{error};
}

template <typename Ptr>
[[nodiscard]] Ptr *check(Ptr *ptr) {
  if (ptr == nullptr) raise();
  return ptr;
}

inline int check(const int code) {
  if (code < 0) raise();
  return code;
}

}

#ifdef DISABLE_SDL_ERROR_CHECK
#  define SDL_CHECK(EXPR) EXPR
#else
#  define SDL_CHECK(EXPR) ::SDL::check(EXPR)
#endif

#endif
