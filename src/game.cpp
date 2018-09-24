//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "factories.hpp"
#include "render system.hpp"
#include "eat dots system.hpp"
#include "movement system.hpp"
#include "player input system.hpp"
#include "wall collide system.hpp"
#include "pursue target system.hpp"
#include "set chase target system.hpp"
#include "set scared target system.hpp"
#include "set scatter target system.hpp"

void Game::init(const Sprite::Sheet &sheet) {
  maze = makeMazeState();
  makeMaze(reg, sheet);
  const Entity player = makePlayer(reg, sheet);
  const Entity blinky = makeBlinky(reg, sheet, player);
  makePinky(reg, sheet, player);
  makeInky(reg, sheet, player, blinky);
  makeClyde(reg, sheet, player);
  dotSprite = sheet.getIDfromName("dot 0");
  rand.seed(std::random_device{}());
}

void Game::input(const SDL_Scancode key) {
  playerInput(reg, key);
}

bool Game::logic() {
  movement(reg);
  wallCollide(reg, maze);
  score += eatDots(reg, maze);
  setBlinkyChaseTarget(reg);
  setPinkyChaseTarget(reg);
  setInkyChaseTarget(reg);
  setClydeChaseTarget(reg);
  setScaredTarget(reg, maze, rand);
  setScatterTarget(reg);
  pursueTarget(reg, maze);
  return true;
}

void Game::render(SDL::QuadWriter &writer, const int frame) {
  mazeRender(reg, writer);
  dotRender(writer, maze, dotSprite);
  playerRender(reg, writer, frame);
  ghostRender(reg, writer, frame);
}