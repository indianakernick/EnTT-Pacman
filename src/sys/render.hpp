//
//  render.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_RENDER_HPP
#define SYS_RENDER_HPP

#include "core/maze.hpp"
#include "util/sprites.hpp"
#include <entt/entity/fwd.hpp>
#include "util/sdl_quad_writer.hpp"

// Render the player (the yellow guy)
void playerRender(entt::registry &, SDL::QuadWriter &, int);

// Render the ghosts
void ghostRender(entt::registry &, SDL::QuadWriter &, int);

// Render the dots and energizers
void dotRender(SDL::QuadWriter &, const MazeState &);

// Render a sprite that covers the whole screen (maze, win, lose)
void fullRender(SDL::QuadWriter &, animera::SpriteID);

#endif
