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

// Functions that read input should return whether they consumed the input.
// If an input function hasn't consumed an input, try the next one.
// Since there is only one input function in this game, we don't really
// need this but I thought I'd show it anyway.

enum class Consumed {
  no,
  yes
};

// This takes the scancode of the key that was pressed and sets the DesiredDir
// of the player.

Consumed playerInput(Registry &, SDL_Scancode);

#endif