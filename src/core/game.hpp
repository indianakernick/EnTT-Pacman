//
//  game.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <random>
#include "maze.hpp"
#include "util/registry.hpp"
#include <SDL2/SDL_scancode.h>
#include <Simpleton/Sprite/sheet.hpp>
#include <Simpleton/SDL/quad writer.hpp>

class Game {
public:
  void init(const Sprite::Sheet &);
  void input(SDL_Scancode);
  bool logic();
  void render(SDL::QuadWriter &, int);

private:
  Registry reg;
  MazeState maze;
  Sprite::ID dotSprite;
  int score = 0;
  std::mt19937 rand;
};

#endif