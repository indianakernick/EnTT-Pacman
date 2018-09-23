//
//  home position component.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 23/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef HOME_POSITION_COMPONENT_HPP
#define HOME_POSITION_COMPONENT_HPP

#include <Simpleton/Grid/pos.hpp>

struct HomePosition {
  Grid::Pos home;
  Grid::Pos scatter;
};

#endif