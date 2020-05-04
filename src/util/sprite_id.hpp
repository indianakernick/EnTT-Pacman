//
//  sprite_id.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 4/5/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//
#ifndef UTIL_SPRITE_ID_HPP
#define UTIL_SPRITE_ID_HPP

#include <cstdint>

using SpriteID = std::uint32_t;
constexpr SpriteID null_id = ~SpriteID{};

#endif
