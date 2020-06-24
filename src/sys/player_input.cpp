//
//  player_input.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 19/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "player_input.hpp"

#include "comp/dir.hpp"
#include "comp/player.hpp"
#include "sys/can_move.hpp"
#include <entt/entity/registry.hpp>

namespace {

Dir readDir(const SDL_Scancode key) {
  switch (key) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      return Dir::up;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
      return Dir::right;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      return Dir::down;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
      return Dir::left;
    default:
      return Dir::none;
  }
}

}

bool playerInput(entt::registry &reg, const SDL_Scancode key) {
  const Dir dir = readDir(key);
  if (dir == Dir::none) {
    return false;
  }
  auto view = reg.view<Player, DesiredDir>();
  for (const entt::entity e : view) {
    view.get<DesiredDir>(e).d = dir;
  }
  return true;
}
