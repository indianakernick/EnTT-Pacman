//
//  player input system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef PLAYER_INPUT_SYSTEM_HPP
#define PLAYER_INPUT_SYSTEM_HPP

#include "registry.hpp"

enum class Consumed {
  no,
  yes
};

Consumed playerInput(Registry &, int);

#endif