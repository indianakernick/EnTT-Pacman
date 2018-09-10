//
//  paths.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <SDL2/SDL.h>

inline std::string SDL::getSaveDir(
  const std::string_view companyName,
  const std::string_view appName
) {
  char *cstr = SDL_GetPrefPath(companyName.data(), appName.data());
  std::string str(cstr);
  SDL_free(cstr);
  return str;
}

inline std::string SDL::getResDir() {
  char *cstr = SDL_GetBasePath();
  std::string str(cstr);
  SDL_free(cstr);
  return str;
}

inline std::string SDL::res(const std::string &name) {
  char *cstr = SDL_GetBasePath();
  std::string out = cstr + name;
  SDL_free(cstr);
  return out;
}
