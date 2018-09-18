//
//  blit sprites system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef BLIT_SPRITES_SYSTEM_HPP
#define BLIT_SPRITES_SYSTEM_HPP

#include "registry.hpp"
#include "framebuf.hpp"
#include <Simpleton/Grid/pos.hpp>

void blitSprites(Registry &, FrameBuf &, Grid::Pos);

#endif