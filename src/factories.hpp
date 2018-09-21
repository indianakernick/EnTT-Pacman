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

// You typically don't need to store the entity ID after making an entity.
// Sometimes you do so it's probably a good idea to return the entity ID
// just in case you need it later.

/*
Entity makePlayer(Registry &, Grid::Pos);
Entity makeGhost(Registry &, Grid::Pos, const FrameBuf &);
Entity makeObject(Registry &, Grid::Pos, const FrameBuf &);
*/

#endif