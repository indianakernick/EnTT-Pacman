//
//  player_input.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "player_input.hpp"

#include "comp/dir.hpp"
#include "comp/player.hpp"
#include "sys/can_move.hpp"
#include <entt/entity/registry.hpp>

namespace {

Grid::Dir readDir(const SDL_Scancode key) {
  switch (key) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      return Grid::Dir::up;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
      return Grid::Dir::right;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      return Grid::Dir::down;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
      return Grid::Dir::left;
    default:
      return Grid::Dir::none;
  }
}

}

Consumed playerInput(entt::registry &reg, const SDL_Scancode key) {
  const Grid::Dir dir = readDir(key);
  if (dir == Grid::Dir::none) {
    return Consumed::no;
  }
  auto view = reg.view<Player, DesiredDir>();
  for (const entt::entity e : view) {
    view.get<DesiredDir>(e).d = dir;
  }
  return Consumed::yes;
}
