//
//  type name.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 18/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_type_name_hpp
#define engine_utils_type_name_hpp

#include <string_view>

namespace Utils {
  template <typename T>
  constexpr std::basic_string_view<char> typeName() {
    //clang   std::basic_string_view<char> Utils::typeName() [T = int]
    //gcc     constexpr std::basic_string_view<char> Utils::typeName() [with T = int]
    std::basic_string_view<char> name = __PRETTY_FUNCTION__;
    name.remove_prefix(name.find('='));
    //trimming "= "
    name.remove_prefix(2);
    //trimming "]"
    name.remove_suffix(1);
    return name;
  }
  
  static_assert(typeName<int>() == "int");
  static_assert(typeName<unsigned>() == "unsigned int");
  
  namespace detail {
    class Dummy {};
  }
  
  static_assert(typeName<detail::Dummy>() == "Utils::detail::Dummy");
  
  template <typename T>
  constexpr size_t typeHash() {
    //djb2
    constexpr std::string_view name = typeName<T>();
    size_t hash = 5381;
    
    for (auto c = name.begin(); c != name.end(); ++c) {
      hash = ((hash << 5) + hash) + *c;
    }

    return hash;
  }
  
  template <typename T0, typename T1>
  constexpr bool typeLess() {
    return typeName<T0>() < typeName<T1>();
  }
}

#endif
