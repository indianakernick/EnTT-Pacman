//
//  sprites.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "sprites.hpp"

// Imagine we're loading these from a files

Sprite<3, 3> makePlayer() {
  Sprite<3, 3> player;
  /*
   O
  -|-
  / \
  */
  player(0, 0) = {' '};
  player(1, 0) = {'O',  color_sys(Color::yellow)};
  player(2, 0) = {' '};
  player(0, 1) = {'-',  color_sys(Color::yellow)};
  player(1, 1) = {'|',  color_sys(Color::red)};
  player(2, 1) = {'-',  color_sys(Color::yellow)};
  player(0, 2) = {'/',  color_sys(Color::blue)};
  player(1, 2) = {' '};
  player(2, 2) = {'\\', color_sys(Color::blue)};
  return player;
}

Sprite<4, 3> makeRock() {
  Sprite<4, 3> rock;
  /*
    __
   /  |
   \_/
  */
  rock(0, 0).ch = ' ';
  rock(1, 0).ch = '_';
  rock(2, 0).ch = '_';
  rock(3, 0).ch = ' ';
  rock(0, 1).ch = '/';
  rock(1, 1).ch = ' ';
  rock(2, 1).ch = ' ';
  rock(3, 1).ch = '|';
  rock(0, 2).ch = '\\';
  rock(1, 2).ch = '_';
  rock(2, 2).ch = '/';
  rock(3, 2).ch = ' ';

  for (Cell &cell : rock) {
    cell.color = color_grey(8);
  }

  return rock;
}

Sprite<4, 4> makeTree() {
  Sprite<4, 4> tree;
  /*
   ##
  ####
   ||
   ||
  */

  const Cell none = {};
  const Cell leaf = {'#', color_rgb(0, 5, 0)};
  const Cell bark = {'|', color_rgb(3, 3, 0)};

  tree(0, 0) = none;
  tree(1, 0) = leaf;
  tree(2, 0) = leaf;
  tree(3, 0) = none;
  tree(0, 1) = leaf;
  tree(1, 1) = leaf;
  tree(2, 1) = leaf;
  tree(3, 1) = leaf;
  tree(0, 2) = none;
  tree(1, 2) = bark;
  tree(2, 2) = bark;
  tree(3, 2) = none;
  tree(0, 3) = none;
  tree(1, 3) = bark;
  tree(2, 3) = bark;
  tree(3, 3) = none;
  
  return tree;
}

Sprite<1, 2> makeFlower() {
  Sprite<1, 2> flower;
  /*
  @
  |
  */

  flower(0, 0) = {'@', color_rgb(5, 0, 5)};
  flower(0, 1) = {'|', color_rgb(0, 5, 0)};
  return flower;
}

Sprite<4, 4> makeMonster() {
  Sprite<4, 4> mon;
  /*
   
  /--\
  |``|
  /~~\
  /  \
  
  */
  mon(0, 0) = {'/', color_sys(Color::red)};
  mon(1, 0) = {'-', color_sys(Color::red)};
  mon(2, 0) = {'-', color_sys(Color::red)};
  mon(3, 0) = {'\\', color_sys(Color::red)};
  mon(0, 1) = {'|', color_sys(Color::red)};
  mon(1, 1) = {'`', color_sys(Color::cyan)};
  mon(2, 1) = {'`', color_sys(Color::cyan)};
  mon(3, 1) = {'|', color_sys(Color::red)};
  mon(0, 2) = {'/', color_sys(Color::yellow)};
  mon(1, 2) = {'~', color_sys(Color::blue)};
  mon(2, 2) = {'~', color_sys(Color::blue)};
  mon(3, 2) = {'\\', color_sys(Color::yellow)};
  mon(0, 3) = {'/', color_sys(Color::yellow)};
  mon(1, 3) = {' ', color_sys(Color::white)};
  mon(2, 3) = {' ', color_sys(Color::white)};
  mon(3, 3) = {'\\', color_sys(Color::yellow)};
  return mon;
}