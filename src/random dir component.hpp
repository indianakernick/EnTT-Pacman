//
//  random dir component.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef RANDOM_DIR_COMPONENT_HPP
#define RANDOM_DIR_COMPONENT_HPP

#include <Simpleton/Grid/dir.hpp>

struct RandomDir {
  Grid::Dir prevDir = Grid::Dir::none;
};

#endif