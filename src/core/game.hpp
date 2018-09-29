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
  enum class State {
  	playing,
  	won,
  	lost
  };

  Registry reg;
  MazeState maze;
  Sprite::ID dotSprite;
  Sprite::ID winSprite;
  Sprite::ID loseSprite;
  int dots = 0;
  std::mt19937 rand;
  State state = State::playing;
  int ticks = 0;
  bool scattering = true;
};

#endif