//
//  render.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef SYS_RENDER_HPP
#define SYS_RENDER_HPP

#include "core/maze.hpp"
#include "util/registry.hpp"
#include <Simpleton/SDL/quad writer.hpp>

void playerRender(Registry &, SDL::QuadWriter &, int);
void ghostRender(Registry &, SDL::QuadWriter &, int);
void dotRender(SDL::QuadWriter &, const MazeState &, Sprite::ID);
void mazeRender(Registry &, SDL::QuadWriter &);

#endif