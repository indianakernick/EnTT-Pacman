//
//  home_position.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 23/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef COMP_HOME_POSITION_HPP
#define COMP_HOME_POSITION_HPP

#include "util/pos.hpp"

struct HomePosition {
  Pos home;    // position in the ghost house
  Pos scatter; // unreachable point in a corner
};

#endif
