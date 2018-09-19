//
//  random movement system.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef RANDOM_MOVEMENT_SYSTEM_HPP
#define RANDOM_MOVEMENT_SYSTEM_HPP

#include <random>
#include "registry.hpp"

void randomMovement(Registry &, std::mt19937 &);

#endif