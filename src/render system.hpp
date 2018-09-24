//
//  render system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "maze.hpp"
#include "registry.hpp"
#include <Simpleton/SDL/quad writer.hpp>

void playerRender(Registry &, SDL::QuadWriter &, int);
void ghostRender(Registry &, SDL::QuadWriter &, int);
void dotRender(SDL::QuadWriter &, const MazeState &, Sprite::ID);
void mazeRender(Registry &, SDL::QuadWriter &);

#endif