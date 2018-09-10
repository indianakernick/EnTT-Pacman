//
//  get.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_get_hpp
#define engine_type_list_get_hpp

#include <string>
#include "foreach.hpp"
#include <experimental/optional>
#include "../Utils/type name.hpp"

namespace List {
  template <typename List, typename Function>
  bool getByName(const std::string_view name, Function &&function) {
    bool gotType = false;
    forEach<List>([&gotType, name, function] (auto t) {
      if (Utils::typeName<LIST_TYPE(t)>() == name) {
        function(t);
        gotType = true;
      }
    });
    return gotType;
  }
  
  class TypeNotFound final : public std::runtime_error {
  public:
    inline explicit TypeNotFound(const std::string_view name)
      : std::runtime_error("Type with name \"" + std::string(name) + "\" not found") {}
  };
  
  template <typename ValueType, typename List, typename Function>
  ValueType getValueByName(const std::string_view name, Function &&function) {
    std::experimental::optional<ValueType> value;
    
    forEach<List>([&value, name, function] (auto t) {
      if (Utils::typeName<LIST_TYPE(t)>() == name) {
        value.emplace(function(t));
      }
    });
    
    if (value) {
      return *value;
    } else {
      throw TypeNotFound(name);
    }
  }
}

#endif
