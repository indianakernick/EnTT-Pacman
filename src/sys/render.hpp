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

// Render the player (the yellow guy)
void playerRender(Registry &, SDL::QuadWriter &, int);
// Render the ghosts
void ghostRender(Registry &, SDL::QuadWriter &, int);
// Render the dots and energizers
void dotRender(SDL::QuadWriter &, const MazeState &, Sprite::ID);
// Render a sprite that covers the whole screen (maze, win-lose)
void fullRender(SDL::QuadWriter &, Sprite::ID);

#endif