//
//  dot render system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef DOT_RENDER_SYSTEM_HPP
#define DOT_RENDER_SYSTEM_HPP

#include "maze.hpp"
#include <Simpleton/SDL/quad writer.hpp>

void dotRender(SDL::QuadWriter &, const MazeState &, Sprite::ID);

#endif