//
//  type.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 3/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_id_type_hpp
#define engine_id_type_hpp

#include <type_traits>
#include "../Utils/type name.hpp"
#include "../Utils/combine hashes.hpp"

namespace ID {
  template <typename Int, typename Group>
  class Counter {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    Counter() = delete;
    ~Counter() = delete;
  
  //Friend declarations shall not declare partial specializations
  protected:
    static Int counter;
  };
  
  template <typename Int, typename Group>
  Int Counter<Int, Group>::counter = 0;
  
  ///Creates an ID unique to the type within the Group. IDs are counted and only
  ///available at runtime
  template <typename Int, typename T, typename Group = void>
  class TypeCounter : private Counter<Int, Group> {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    TypeCounter() = delete;
    ~TypeCounter() = delete;
    
    static Int get() {
      return ID;
    }
    
  private:
    static const Int ID;
  };
  
  template <typename Int, typename T, typename Group>
  const Int TypeCounter<Int, T, Group>::ID = Counter<Int, Group>::counter++;
  
  ///Creates an ID unique to the type within the Group. IDs are hashes and
  ///available at compile time
  template <typename Int, typename T, typename Group = void>
  class TypeHasher {
  public:
    TypeHasher() = delete;
    ~TypeHasher() = delete;
    
    static constexpr Int get() {
      return static_cast<Int>(
        Utils::combineHashes(Utils::typeHash<Group>(), Utils::typeHash<T>())
      );
    }
  };
}

#endif
