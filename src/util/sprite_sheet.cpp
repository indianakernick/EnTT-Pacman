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

namespace {

void expect(std::istream &stream, const std::string_view expected) {
  std::string actual(expected.size(), ' ');
  stream.read(actual.data(), expected.size());
  if (!stream || actual != expected) {
    throw std::runtime_error("Expected \"" + std::string{expected} + "\"");
  }
}

void expect(std::istream &stream, const char expected) {
  const char actual = stream.get();
  if (!stream || actual != expected) {
    throw std::runtime_error("Expected '" + std::string{1, actual} + "'");
  }
}

bool check(std::istream &stream, const char expected) {
  if (stream.peek() == expected) {
    stream.ignore();
    return true;
  } else {
    return false;
  }
}

}

SpriteSheet::SpriteSheet(const std::string &path) {
  std::ifstream file{path};
  if (!file.is_open()) {
    throw std::runtime_error{"Failed to open file"};
  }

  file.seekg(0, std::ios_base::end);
  const long size = file.tellg();
  file.seekg(0, std::ios_base::beg);

  expect(file, "{\"length\":");
  file >> length_;
  expect(file, ",\"names\":{");

  while (true) {
    expect(file, '"');
    std::string name;
    std::getline(file, name, '"');
    expect(file, ':');

    SpriteID id;
    file >> id;

    names.emplace(name, id);

    if (check(file, '}')) {
      break;
    } else {
      expect(file, ',');
    }
  }

  rects.reserve(names.size());
  expect(file, ",\"rects\":[");

  while (true) {
    SpriteRect rect;
    expect(file, '[');
    file >> rect.min.x;
    expect(file, ',');
    file >> rect.min.y;
    expect(file, ',');
    file >> rect.max.x;
    expect(file, ',');
    file >> rect.max.y;
    expect(file, ']');

    rects.push_back(rect);

    if (check(file, ']')) {
      break;
    } else {
      expect(file, ',');
    }
  }

  expect(file, "}\n");
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