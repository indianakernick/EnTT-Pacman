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
  player(0, 0) = {' ',  Color::white,  Color::black};
  player(1, 0) = {'O',  Color::yellow, Color::black};
  player(2, 0) = {' ',  Color::white,  Color::black};
  player(0, 1) = {'-',  Color::yellow, Color::black};
  player(1, 1) = {'|',  Color::red,    Color::black};
  player(2, 1) = {'-',  Color::yellow, Color::black};
  player(0, 2) = {'/',  Color::blue,   Color::black};
  player(1, 2) = {' ',  Color::white,  Color::black};
  player(2, 2) = {'\\', Color::blue,   Color::black};
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
    cell.fore = Color::white;
    cell.back = Color::black;
  	cell.attr = Attr::dim;
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
  const Cell leaf = {'#', Color::green, Color::black, Attr::normal};
  // Hoping dim yellow is brown
  const Cell bark = {'|', Color::yellow, Color::black, Attr::dim};

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

  flower(0, 0) = {'@', Color::magenta, Color::black, Attr::normal};
  flower(0, 1) = {'|', Color::green, Color::black, Attr::normal};
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
  mon(0, 0) = {'/', Color::red};
  mon(1, 0) = {'-', Color::red};
  mon(2, 0) = {'-', Color::red};
  mon(3, 0) = {'\\', Color::red};
  mon(0, 1) = {'|', Color::red};
  mon(1, 1) = {'`', Color::cyan};
  mon(2, 1) = {'`', Color::cyan};
  mon(3, 1) = {'|', Color::red};
  mon(0, 2) = {'/', Color::yellow};
  mon(1, 2) = {'~', Color::blue};
  mon(2, 2) = {'~', Color::blue};
  mon(3, 2) = {'\\', Color::yellow};
  mon(0, 3) = {'/', Color::yellow};
  mon(1, 3) = {' ', Color::white};
  mon(2, 3) = {' ', Color::white};
  mon(3, 3) = {'\\', Color::yellow};
  return mon;
}