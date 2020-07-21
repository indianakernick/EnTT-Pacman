//
//  game.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 22/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "game.hpp"

#include "constants.hpp"
#include "sys/house.hpp"
#include "sys/render.hpp"
#include "sys/eat_dots.hpp"
#include "sys/movement.hpp"
#include "core/factories.hpp"
#include "sys/set_target.hpp"
#include "sys/player_input.hpp"
#include "sys/pursue_target.hpp"
#include "sys/change_ghost_mode.hpp"
#include "sys/player_ghost_collide.hpp"

void Game::init() {
  maze = makeMazeState();
  const entt::entity player = makePlayer(reg);
  const entt::entity blinky = makeBlinky(reg, player);
  makePinky(reg, player);
  makeInky(reg, player, blinky);
  makeClyde(reg, player);
  // seeding a pseudo random number generator with a random source
  rand.seed(std::random_device{}());
}

void Game::input(const SDL_Scancode key) {
  if (state == State::playing) {
    playerInput(reg, key);
  }
}

bool Game::logic() {
  // The order of systems is very important in an ECS. Each system reads some
  // state and modifies some state. If the state isn't read and modified in the
  // right order, subtle bugs can occur. Make sure that the order of systems is
  // easy to see (i.e. not hidden away by some abstraction that sets the order
  // for you). Always think carefully about the order that systems should be in.

  // It's OK to keep some game state outside of the ECS (e.g. maze, dots,
  // dotSprite) but try to keep as much state within the ECS as you can.
  // Keeping too much state outside of the ECS can lead to problems.
  // For example: `dots` is the amount of dots eaten by the player. If there
  // were more than one player, then each player might want to keep track of how
  // many dots they've eaten. So `dots` would have to be moved into a component

  if (state != State::playing) {
    return true;
  }

  if (scattering) {
    if (ticks >= scatterTicks) {
      ghostChase(reg);
      ticks = 0;
      scattering = false;
    }
  } else {
    if (ticks >= chaseTicks) {
      ghostScatter(reg);
      ticks = 0;
      scattering = true;
    }
  }
  ++ticks;

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
    fullRender(writer, animera::SpriteID::maze);
    dotRender(writer, maze);
    playerRender(reg, writer, frame);
    ghostRender(reg, writer, frame);
  } else if (state == State::won) {
    fullRender(writer, animera::SpriteID::win);
  } else if (state == State::lost) {
    fullRender(writer, animera::SpriteID::lose);
  }
}
