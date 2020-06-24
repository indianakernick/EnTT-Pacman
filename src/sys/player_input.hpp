//
//  player_input.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 19/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_PLAYER_INPUT_HPP
#define SYS_PLAYER_INPUT_HPP

#include <SDL_scancode.h>
#include <entt/entity/fwd.hpp>

// Functions that read input should return whether they consumed the input.
// If an input function hasn't consumed an input, try the next one.
// Since there is only one input function in this game, we don't really
// need this but I thought I'd show it anyway.

// This takes the scancode of the key that was pressed and sets the DesiredDir
// of the player.

bool playerInput(entt::registry &, SDL_Scancode);

#endif
