//
//  audio library.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/1/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline void SDL::detail::deleteAudioLibrary(const bool initialized) {
  if (initialized) {
    Mix_CloseAudio();
    Mix_Quit();
  }
}

inline SDL::AudioLibrary SDL::makeAudioLibrary(const AudioLibParams &p) {
  if (Mix_Init(p.codecFlags) != p.codecFlags) {
    // SDL_Mixer uses SDL's error system
    throw SDL::Error();
  }
  
  CHECK_SDL_ERROR(Mix_OpenAudio(p.frequency, p.format, p.channels, p.chunksize));
  
  return AudioLibrary(true);
}
