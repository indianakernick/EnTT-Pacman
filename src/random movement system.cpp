//
//  random movement system.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "random movement system.hpp"

#include <Simpleton/Math/rand.hpp>
#include "random dir component.hpp"
#include "desired dir component.hpp"

void randomMovement(Registry &reg, std::mt19937 &rand) {
  auto view = reg.view<RandomDir, DesiredDir>();
  for (const Entity e : view) {
  	Grid::Dir &prevDir = view.get<RandomDir>(e).prevDir;
    Grid::Dir &newDir = view.get<DesiredDir>(e).d;
  	const float dist[5] = {
  	  0.4f, // same dir
  	  0.2f, // other
  	  0.1f, // opposite dir
  	  0.2f, // other
  	  0.1f  // stop
  	};
  	const size_t choice = Math::weightedRand(rand, std::cbegin(dist), std::cend(dist));
  	if (choice == 4) {
  	  newDir = Grid::Dir::none;
  	} else {
  	  newDir = Grid::rotateCW(prevDir, choice);
  	}
  	prevDir = newDir;
  }
}