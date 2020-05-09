//
//  house.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 29/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef SYS_HOUSE_HPP
#define SYS_HOUSE_HPP

#include <entt/entity/fwd.hpp>

// These systems deal with ghosts entering and leaving the house

void enterHouse(entt::registry &);
void leaveHouse(entt::registry &);

#endif
