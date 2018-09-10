//
//  object types.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_object_types_hpp
#define engine_box2d_object_types_hpp

#ifndef OBJECT_TYPES
/*
An example of a possible definition of OBJECT_TYPES is this

#define OBJECT_TYPES                                                            \
  OBJECT_TYPE(PlayerBody)                                                       \
  OBJECT_TYPE(PlayerFoot)                                                       \
  OBJECT_TYPE(Ground)                                                           \
  OBJECT_TYPE(Sensor)                                                           \
  LAST_OBJECT_TYPE(Button)
*/
#error "Must #define OBJECT_TYPES before #including this header"
#else

#include <string>
#include <cstdint>
#include "../Type List/get.hpp"
#include "../Type List/index.hpp"

namespace B2 {
  using ObjectTypeID = uint16_t;

  namespace ObjT {
    #define OBJECT_TYPE(NAME) class NAME {};
    #define LAST_OBJECT_TYPE(NAME) OBJECT_TYPE(NAME)
    OBJECT_TYPES
    #undef LAST_OBJECT_TYPE
    #undef OBJECT_TYPE
  }
  
  using ObjectTypes = List::Type<
    #define OBJECT_TYPE(NAME) ObjT::NAME,
    #define LAST_OBJECT_TYPE(NAME) ObjT::NAME
    OBJECT_TYPES
    #undef LAST_OBJECT_TYPE
    #undef OBJECT_TYPE
  >;

  template <typename ObjectType>
  ObjectTypeID getObjectTypeID() {
    return static_cast<ObjectTypeID>(List::IndexOf<ObjectTypes, ObjectType>);
  }

  template <typename ObjectType>
  void *getObjectTypeUserData() {
    return reinterpret_cast<void *>(
      static_cast<uintptr_t>(getObjectTypeID<ObjectType>())
    );
  }

  inline ObjectTypeID getObjectTypeID(const void *const userData) {
    return static_cast<ObjectTypeID>(
      reinterpret_cast<uintptr_t>(userData)
    );
  }
  
  inline void *getObjectTypeUserData(const std::string &objectTypeName) {
    try {
      return List::getValueByName<void *, ObjectTypes>(
        "B2::ObjT::" + objectTypeName,
        [] (const auto t) {
          return getObjectTypeUserData<LIST_TYPE(t)>();
        }
      );
    } catch (List::TypeNotFound &) {
      throw std::runtime_error("Invalid object type name");
    }
  }
}

#endif // OBJECT_TYPES

#endif
