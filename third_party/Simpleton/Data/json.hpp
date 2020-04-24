//
//  json.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_data_json_hpp
#define engine_data_json_hpp

#include <glm/vec2.hpp>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Data {
  template <typename T>
  void getOptional(T &dst, const json &node, const char *const name) {
    const auto iter = node.find(name);
    if (iter != node.cend()) {
      dst = iter->get<T>();
    }
  }
  
  template <typename T>
  void get(T &dst, const json &node, const char *const name) {
    dst = node.at(name).get<T>();
  }
}

#define JSON_OPTIONAL(CHILD_ITER, PARENT_NODE, CHILD_NAME)                      \
  const auto CHILD_ITER = PARENT_NODE.find(CHILD_NAME);                         \
  CHILD_ITER != PARENT_NODE.end()

#define DATA_GET(OBJ, NAME) Data::get(OBJ.NAME, j, #NAME)
#define DATA_GET_OPT(OBJ, NAME) Data::getOptional(OBJ.NAME, j, #NAME)

namespace glm {
  template <typename T>
  void from_json(const json &j, glm::tvec2<T> &vec) {
    vec.x = j.at(0).get<T>();
    vec.y = j.at(1).get<T>();
  }
}

#endif
