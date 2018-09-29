//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "constants.hpp"
#include "sys/house.hpp"
#include "sys/render.hpp"
#include "sys/eat_dots.hpp"
#include "sys/movement.hpp"
#include "core/factories.hpp"
#include "sys/player_input.hpp"
#include "sys/pursue_target.hpp"
#include "sys/set_chase_target.hpp"
#include "sys/set_eaten_target.hpp"
#include "sys/change_ghost_mode.hpp"
#include "sys/set_scared_target.hpp"
#include "sys/set_scatter_target.hpp"
#include "sys/player_ghost_collide.hpp"

void Game::init(const Sprite::Sheet &sheet) {
  maze = makeMazeState();
  makeMaze(reg, sheet);
  const Entity player = makePlayer(reg, sheet);
  const Entity blinky = makeBlinky(reg, sheet, player);
  makePinky(reg, sheet, player);
  makeInky(reg, sheet, player, blinky);
  makeClyde(reg, sheet, player);
  dotSprite = sheet.getIDfromName("dot 0");
  winSprite = sheet.getIDfromName("win");
  loseSprite = sheet.getIDfromName("lose");
  rand.seed(std::random_device{}());
}

void Game::input(const SDL_Scancode key) {
  if (state == State::playing) {
    playerInput(reg, key);
  }
}

bool Game::logic() {
  // The order systems is very important in an ECS.
  // Each system reads some state and modifies some state.
  // If the state isn't read and modified in the right order,
  // subtle bugs can occur. Make sure that the order of systems is easy to see.
  // i.e. not hidden away by some abstraction that sets the order for you.
  // Always think carefully about the order that systems should be in.

  // It's OK to keep some game state outside of the ECS. e.g. maze, dots, dotSprite
  // But try to keep as much state within the ECS as you can though.
  // Keeping too much state outside of the ECS can lead to problems. For example:
  // `dots` is the amount of dots eaten by the player. If there were more than
  // one player, then each player might want to keep track of how many dots
  // they've eaten. So `dots` would have to be moved into a component

  if (state != State::playing) {
  	return true;
  }

  movement(reg);
  wallCollide(reg, maze);
  dots += eatDots(reg, maze);
  if (eatEnergizer(reg, maze)) {
  	ghostScared(reg);
  }
  ghostScaredTimeout(reg);
  enterHouse(reg);
  setBlinkyChaseTarget(reg);
  setPinkyChaseTarget(reg);
  setInkyChaseTarget(reg);
  setClydeChaseTarget(reg);
  setScaredTarget(reg, maze, rand);
  setScatterTarget(reg);
  setEatenTarget(reg);
  leaveHouse(reg);
  pursueTarget(reg, maze);

  const GhostCollision collision = playerGhostCollide(reg);
  if (collision.type == GhostCollision::Type::eat) {
  	ghostEaten(reg, collision.ghost);
  }
  if (collision.type == GhostCollision::Type::lose) {
    state = State::lost;
  } else if (dots == dotsInMaze) {
    state = State::won;
  }
  return true;
}

void Game::render(SDL::QuadWriter &writer, const int frame) {
  if (state == State::playing) {
    mazeRender(reg, writer);
    dotRender(writer, maze, dotSprite);
    playerRender(reg, writer, frame);
    ghostRender(reg, writer, frame);
  } else if (state == State::won) {
  	winloseRender(writer, winSprite);
  } else if (state == State::lost) {
  	winloseRender(writer, loseSprite);
  }
}