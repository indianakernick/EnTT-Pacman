//
//  dir.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_DIR_HPP
#define COMP_DIR_HPP

#include <Simpleton/Grid/dir.hpp>

struct DesiredDir {
  Grid::Dir d = Grid::Dir::none;
};

struct ActualDir {
  Grid::Dir d = Grid::Dir::none;
};

#endif