//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "factories.hpp"
#include "movement system.hpp"
#include "maze render system.hpp"
#include "player input system.hpp"
#include "wall collide system.hpp"
#include "player render system.hpp"

void Game::init(const Sprite::Sheet &sheet) {
  maze = makeMazeState();
  makeMaze(reg, sheet);
  makePlayer(reg, sheet);
}

void Game::input(const SDL_Scancode key) {
  playerInput(reg, key);
}

bool Game::logic() {
  wallCollide(reg, maze);
  movement(reg);
  return true;
}

void Game::render(SDL::QuadWriter &writer, const int frame) {
  mazeRender(reg, writer);
  playerRender(reg, writer, frame);
}