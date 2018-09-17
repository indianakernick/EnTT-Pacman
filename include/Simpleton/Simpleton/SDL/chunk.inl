//
//  chunk.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline void SDL::detail::deleteChunk(Mix_Chunk *const chunk) {
  Mix_FreeChunk(chunk);
}

inline void SDL::Chunk::play(const int channel, const int loops, const int ticks) {
  Mix_PlayChannelTimed(channel, chunk, loops, ticks);
}

inline SDL::Chunk SDL::loadWAV(const char *const file) {
  return Chunk(CHECK_SDL_NULL(Mix_LoadWAV(file)));
}
