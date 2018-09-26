//
//  player_input.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_PLAYER_INPUT_HPP
#define SYS_PLAYER_INPUT_HPP

#include "util/registry.hpp"
#include <SDL2/SDL_scancode.h>

enum class Consumed {
  no,
  yes
};

Consumed playerInput(Registry &, SDL_Scancode);

#endif