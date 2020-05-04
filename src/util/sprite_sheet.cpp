//
//  sprite_sheet.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 4/5/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//

#include "sprite_sheet.hpp"

#include <fstream>
#include <stdexcept>
#include <Simpleton/Utils/parse string.hpp>

SpriteSheet::SpriteSheet(const std::string &path) {
  std::ifstream file{path};
  if (!file.is_open()) {
    throw std::runtime_error{"Failed to open file"};
  }

  file.seekg(0, std::ios_base::end);
  const long size = file.tellg();
  file.seekg(0, std::ios_base::beg);

  auto buffer = std::make_unique<char []>(size);
  file.read(buffer.get(), size);

  Utils::ParseString string(buffer.get(), size);

  string.expect("{\"length\":");
  string.parseNumber(length_);
  string.expect(",\"names\":{");
  while (true) {
    string.expect('"');
    std::string name;
    string.copyUntil(name, '"');
    string.expect("\":");
    names.emplace(name, string.parseNumber<SpriteID>());
    if (string.check('}')) {
      break;
    } else {
      string.expect(',');
    }
  }

  rects.reserve(names.size());
  string.expect(",\"rects\":[");
  while (true) {
    SpriteRect rect;
    string.expect('[');
    string.parseNumber(rect.min.x);
    string.expect(',');
    string.parseNumber(rect.min.y);
    string.expect(',');
    string.parseNumber(rect.max.x);
    string.expect(',');
    string.parseNumber(rect.max.y);
    string.expect(']');

    rect.min /= glm::vec2(length_);
    rect.max /= glm::vec2(length_);
    rects.push_back(rect);

    if (string.check(']')) {
      break;
    } else {
      string.expect(',');
    }
  }

  string.expect("}\n");
}

SpriteID SpriteSheet::lookup(const std::string_view name) const {
  // We can eliminate the conversion to std::string in C++20
  const auto iter = names.find(std::string(name));
  return iter == names.end() ? null_id : iter->second;
}

SpriteRect SpriteSheet::get(const SpriteID id) const {
  return rects.at(static_cast<std::size_t>(id));
}

std::uint32_t SpriteSheet::length() const {
  return length_;
}