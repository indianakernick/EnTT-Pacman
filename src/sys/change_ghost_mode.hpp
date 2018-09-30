//
//  change_ghost_mode.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 29/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_CHANGE_GHOST_MODE_HPP
#define SYS_CHANGE_GHOST_MODE_HPP

#include "util/registry.hpp"

// This is called when pacman eats an energizer. All ghosts in chase or scatter
// mode will be put into scared mode. Ghosts that are already in scared mode
// will have there scared timer extended
void ghostScared(Registry &);
// Ghosts in scared mode have a timer. When the timer runs out, they will enter
// chase mode.
void ghostScaredTimeout(Registry &);
// This is called when pacman collides with a ghost that is in scared mode.
// This system puts the ghost into eaten mode
void ghostEaten(Registry &, Entity);
// Puts all of the ghosts into scatter mode
void ghostScatter(Registry &);
// Puts all of the ghost into chase mode
void ghostChase(Registry &);

#endif