//
//  factories.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include "registry.hpp"
#include <Simpleton/Grid/pos.hpp>

Entity makePlayer(Registry &, Grid::Pos);
Entity makeRock(Registry &, Grid::Pos);

#endif