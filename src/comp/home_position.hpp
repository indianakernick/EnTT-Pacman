//
//  home_position.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_HOME_POSITION_HPP
#define COMP_HOME_POSITION_HPP

#include <Simpleton/Grid/pos.hpp>

struct HomePosition {
  Grid::Pos home;    // position in the ghost house
  Grid::Pos scatter; // unreachable point in a corner
};

#endif
