//
//  game.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <random>
#include "maze.hpp"
#include <SDL_scancode.h>
#include "../util/sprite_sheet.hpp"
#include <entt/entity/registry.hpp>
#include "../util/sdl_quad_writer.hpp"

class Game {
public:
  void init(const SpriteSheet &);
  void input(SDL_Scancode);
  bool logic();
  void render(SDL::QuadWriter &, int);

private:
  enum class State {
    playing,
    won,
    lost
  };

  entt::registry reg;
  MazeState maze;
  SpriteID dotSprite;
  SpriteID winloseSprite;
  SpriteID mazeSprite;
  int dots = 0;
  std::mt19937 rand;
  State state = State::playing;
  int ticks = 0;
  bool scattering = true;
};

#endif
