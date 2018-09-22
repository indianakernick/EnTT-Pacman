//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "factories.hpp"
#include "maze render system.hpp"

void Game::init(const Sprite::Sheet &sheet) {
  makeMaze(reg, sheet);
}

void Game::input(const SDL_Scancode key) {
  
}

bool Game::logic() {
  return true;
}

void Game::render(SDL::QuadWriter &writer, const int frame) {
  mazeRender(reg, writer);
} 