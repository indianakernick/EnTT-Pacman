//
//  sprite_sheet.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 4/5/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//

#ifndef UTIL_SPRITE_SHEET_HPP
#define UTIL_SPRITE_SHEET_HPP

#include <string>
#include <vector>
#include "pos.hpp"
#include <cstdint>
#include <string_view>
#include <unordered_map>
#include "sprite_id.hpp"

// This file is temporary.
// Soon we won't need to parse anything...

struct SpriteRect {
  Pos min;
  Pos max;
};

class SpriteSheet {
public:
  explicit SpriteSheet(const std::string &);

  SpriteID lookup(std::string_view) const;
  SpriteRect get(SpriteID) const;
  std::uint32_t length() const;

private:
  std::unordered_map<std::string, SpriteID> names;
  std::vector<SpriteRect> rects;
  std::uint32_t length_;
};

#endif
