//
//  home_position.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_HOME_POSITION_HPP
#define COMP_HOME_POSITION_HPP

#include <Simpleton/Grid/pos.hpp>

struct HomePosition {
  Grid::Pos home;
  Grid::Pos scatter;
};

#endif