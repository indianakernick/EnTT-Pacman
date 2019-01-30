//
//  dir.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_DIR_HPP
#define COMP_DIR_HPP

#include <Simpleton/Grid/dir.hpp>

// The direction that the entity wants to go
struct DesiredDir {
  Grid::Dir d = Grid::Dir::none;
};

// The direction that the entity is actually going in
struct ActualDir {
  Grid::Dir d = Grid::Dir::none;
};

#endif
