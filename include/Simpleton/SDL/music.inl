//
//  music.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/1/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline void SDL::detail::deleteMusic(Mix_Music *const music) {
  Mix_FreeMusic(music);
}

inline void SDL::Music::play(const int loops) {
  CHECK_SDL_ERROR(Mix_PlayMusic(music, loops));
}

inline SDL::Music SDL::makeMusic(const char *const file) {
  return Music(CHECK_SDL_NULL(Mix_LoadMUS(file)));
}
