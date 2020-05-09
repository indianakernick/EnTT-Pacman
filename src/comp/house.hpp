//
//  house.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 27/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef COMP_HOUSE_HPP
#define COMP_HOUSE_HPP

// These tag components are sort of like tickets. Ghosts are only allowed
// to go through the door if they have the EnterHouse or LeaveHouse tags.
// There are dedicated systems that deal with entering and leaving the
// ghost house.

struct EnterHouse {};
struct LeaveHouse {};

#endif
