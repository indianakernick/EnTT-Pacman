//
//  chase_target.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 24/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef COMP_CHASE_TARGET_HPP
#define COMP_CHASE_TARGET_HPP

#include "util/registry.hpp"

// These components define the chase targeting behavior for each ghost

// This is where the beauty in ECS comes in
// Blinky doesn't have to chase the player!
// The BlinkyChaseTarget component stores the ID of an entity that
// has a Position component. That's it! Blinky can chase anything
// that has a Position. We could quite easily make blinky chase inky

struct BlinkyChaseTarget {
  Entity player;
};

struct PinkyChaseTarget {
  Entity player;
};

struct InkyChaseTarget {
  Entity player;
  Entity blinky;
};

struct ClydeChaseTarget {
  Entity player;
};

#endif