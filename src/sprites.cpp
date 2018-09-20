//
//  sprites.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "sprites.hpp"

// Imagine we're loading these from a files

namespace {

template <size_t Size>
void spriteStr(FrameBuf &buf, const char (&str)[Size]) {
  assert(buf.area() + 1 == Size);
  for (size_t i = 0; i != Size - 1; ++i) {
  	buf[i].ch = str[i];
  }
}

}

FrameBuf makePlayerSprite() {
  FrameBuf player{3, 3};
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

FrameBuf makeRockSprite() {
  FrameBuf rock{4, 3};
  const char str[13] = {
  	" ## "
  	"####"
  	" ## "
  };
  spriteStr(rock, str);
  for (Cell &cell : rock) {
    cell.color = color_grey(8);
  }

  return rock;
}

FrameBuf makeTreeSprite() {
  FrameBuf tree{4, 4};
  /*
   ##
  ####
   ||
   ||
  */

  const Cell none = {};
  const Cell leaf = {'#', color_rgb(0, 5, 0)};
  const Cell bark = {'|', color_rgb(3, 1, 0)};

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

FrameBuf makeFlowerSprite() {
  FrameBuf flower{1, 2};
  /*
  @
  |
  */

  flower(0, 0) = {'@', color_rgb(5, 0, 5)};
  flower(0, 1) = {'|', color_rgb(0, 5, 0)};
  return flower;
}

FrameBuf makeMonsterSprite() {
  FrameBuf mon{4, 4};
  /*
   
  /--\
  |``|
  /~~\
  /  \
  
  */

  const ColIdx topHead = color_rgb(2, 0, 0);
  const ColIdx sideHead = color_rgb(3, 0, 1);
  const ColIdx arms = color_rgb(4, 1, 0);
  const ColIdx chest = color_rgb(2, 0, 2);
  const ColIdx eyes = color_rgb(0, 5, 5);
   
  mon(0, 0) = {'/', topHead};
  mon(1, 0) = {'-', topHead};
  mon(2, 0) = {'-', topHead};
  mon(3, 0) = {'\\', topHead};
  mon(0, 1) = {'|', sideHead};
  mon(1, 1) = {'`', eyes};
  mon(2, 1) = {'`', eyes};
  mon(3, 1) = {'|', sideHead};
  mon(0, 2) = {'/', arms};
  mon(1, 2) = {'~', chest};
  mon(2, 2) = {'~', chest};
  mon(3, 2) = {'\\', arms};
  mon(0, 3) = {'/', arms};
  mon(1, 3) = {' '};
  mon(2, 3) = {' '};
  mon(3, 3) = {'\\', arms};
  
  return mon;
}

/*
###################
#        #        #
# ## ### # ### ## #
# ## ### # ### ## #
#                 #
# ## # ##### # ## #
#    #   #   #    #
#### ### # ### ####
   # #       # #
#### # ##### # ####
       #   #
#### # ##### # ####
   # #       # #    
#### # ##### # ####
#        #        #
# ## ### # ### ## #
#  #           #  #
## # # ##### # # ##
#    #   #   #    #
# ###### # ###### #
#                 #
###################

19, 22
*/

FrameBuf makeTestSprite() {
  FrameBuf test{19*3, 22*3};
  const char str[19*3 * 22*3 + 1] = {
  	"/-------------------------------------------------------\\"
  	"|                                                       |"
  	"| /------------------------\\ /------------------------\\ |"

  	"| |                        | |                        | |"
  	"| |                        | |                        | |"
  	"| |                        | |                        | |"

  	"| |   /----\\   /-------\\   | |   /-------\\   /----\\   | |"
  	"| |   |    |   |       |   | |   |       |   |    |   | |"
  	"| |   |    |   |       |   | |   |       |   |    |   | |"

  	"| |   |    |   |       |   | |   |       |   |    |   | |"
  	"| |   |    |   |       |   | |   |       |   |    |   | |" 
  	"| |   \\----/   \\-------/   \\-/   \\-------/   \\----/   | |"

    "| |                                                   | |"
   	"| |                                                   | |"
   	"| |                                                   | |"

   	"| |   /----\\   /-\\   /-------------\\   /-\\   /----\\   | |"
   	"| |   |    |   | |   |             |   | |   |    |   | |"
   	"| |   \\----/   | |   \\-----\\ /-----/   | |   \\----/   | |"

   	"| |            | |         | |         | |            | |"
   	"| |            | |         | |         | |            | |"
   	"| |            | |         | |         | |            | |"

   	"| \\--------\\   | \\-----\\   | |   /-----/ |   /--------/ |"
   	"|          |   |       |   | |   |       |   |          |"
   	"\\--------\\ |   | /-----/   \\-/   \\-----\\ |   | /--------/"

    "         | |   | |                     | |   | |         "
    "         | |   | |                     | |   | |         "
    "         | |   | |                     | |   | |         "

    "---------/ |   | |   /-----###-----\\   | |   | \\---------"
    "           |   | |   |             |   | |   |           "
    "-----------/   \\-/   | /---###---\\ |   \\-/   \\-----------"   	

    "                     | |         | |                     "
    "                     | |         | |                     "
    "                     | |         | |                     "

    "-----------\\   /-\\   | \\---------/ |   /-\\   /-----------"
    "           |   | |   |             |   | |   |           "
    "---------\\ |   | |   \\-------------/   | |   | /---------"

    "         | |   | |                     | |   | |         "
    "         | |   | |                     | |   | |         "
    "         | |   | |                     | |   | |         "

    "/--------/ |   | |   /-------------\\   | |   | \\--------\\"
    "|          |   | |   |             |   | |   |          |"
    "| /--------/   \\-/   \\-----\\ /-----/   \\-/   \\--------\\ |"

    "| |                        | |                        | |"
    "| |                        | |                        | |"
    "| |                        | |                        | |"

    "| |   /----\\   /-------\\   | |   /-------\\   /----\\   | |"
    "| |   |    |   |       |   | |   |       |   |    |   | |"
    "| |   \\--\\ |   \\-------/   \\-/   \\-------/   | /--/   | |"

    "| |      | |                                 | |      | |"
    "| |      | |                                 | |      | |"
    "| |      | |                                 | |      | |"

    "| \\--\\   | |   /-\\   /-------------\\   /-\\   | |   /--/ |"
    "|    |   | |   | |   |             |   | |   | |   |    |"
    "| /--/   \\-/   | |   \\-----\\ /-----/   | |   \\-/   \\--\\ |"

    "| |            | |         | |         | |            | |"
    "| |            | |         | |         | |            | |"
    "| |            | |         | |         | |            | |"

    "| |   /--------/ \\-----\\   | |   /-----/ \\--------\\   | |"
    "| |   |                |   | |   |                |   | |"
    "| |   \\----------------/   \\-/   \\----------------/   | |"

    "| |                                                   | |"
    "| |                                                   | |"
    "| |                                                   | |"

    "| \\---------------------------------------------------/ |"
    "|                                                       |"
    "\\-------------------------------------------------------/"
  };

  /*FrameBuf test{19, 22};
  const char str[] = {
  	"###################"
  	"#        #        #"
  	"# ## ### # ### ## #"
  	"# ## ### # ### ## #"
  	"#                 #"
  	"# ## # ##### # ## #"
  	"#    #   #   #    #"
  	"#### ### # ### ####"
  	"   # #       # #   "
  	"#### # ##### # ####"
  	"       #   #       "
  	"#### # ##### # ####"
  	"   # #       # #   "
  	"#### # ##### # ####"
  	"#        #        #"
  	"# ## ### # ### ## #"
  	"#  #           #  #"
  	"## # # ##### # # ##"
  	"#    #   #   #    #"
  	"# ###### # ###### #"
  	"#                 #"
  	"###################"
  };*/
  spriteStr(test, str);
  for (Cell &cell : test) {
  	cell.color = color_rgb(0, 0, 5);
  }
  for (Grid::Coord y = 0; y != 3; ++y) {
    for (Grid::Coord x = 0; x != 3; ++x) {
      test(9 * 3 + x, 9 * 3 + y).color = color_sys(Color::white);
    }
  }  
  return test;
}