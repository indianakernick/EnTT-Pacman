//
//  player_input.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "player_input.hpp"

#include "comp/dir.hpp"
#include "comp/player.hpp"

namespace {

Grid::Dir readDir(const SDL_Scancode key) {
         if (key == SDL_SCANCODE_UP    || key == SDL_SCANCODE_W) {
    return Grid::Dir::up;
  } else if (key == SDL_SCANCODE_RIGHT || key == SDL_SCANCODE_D) {
  	return Grid::Dir::right;
  } else if (key == SDL_SCANCODE_DOWN  || key == SDL_SCANCODE_S) {
  	return Grid::Dir::down;
  } else if (key == SDL_SCANCODE_LEFT  || key == SDL_SCANCODE_A) {
  	return Grid::Dir::left;
  } else {
  	return Grid::Dir::none;
  }
}

}

Consumed playerInput(Registry &reg, const SDL_Scancode key) {
  const Grid::Dir dir = readDir(key);
  if (dir == Grid::Dir::none) {
  	return Consumed::no;
  }
  auto view = reg.view<Player, DesiredDir>();
  for (const Entity e : view) {
    view.get<DesiredDir>(e).d = dir;
  }
  return Consumed::yes;
}