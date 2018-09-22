//
//  player render system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef PLAYER_RENDER_SYSTEM_HPP
#define PLAYER_RENDER_SYSTEM_HPP

#include "registry.hpp"
#include <Simpleton/SDL/quad writer.hpp>

void playerRender(Registry &, SDL::QuadWriter &, int);

#endif