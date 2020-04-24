//
//  type enum.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_type_enum_hpp
#define engine_opengl_type_enum_hpp

#include "opengl.hpp"
#include "../Utils/meta glm.hpp"

namespace GL {
  #define TYPE_ENUM(TYPE, ENUM)                                                 \
    template <>                                                                 \
    struct TypeEnum<TYPE> {                                                     \
      static constexpr GLenum type = ENUM;                                      \
      static constexpr GLsizei size = 1;                                        \
    };
  
  template <typename Vector>
  struct TypeEnum {
    static_assert(Utils::is_vec<Vector>);
    static constexpr GLenum type = TypeEnum<Utils::vec_value_type<Vector>>::type;
    static constexpr GLsizei size = Utils::vec_size<Vector>;
  };

  //GLboolean is defined as a uint8_t so the types conflict
  
  TYPE_ENUM(bool, GL_BOOL)
  TYPE_ENUM(GLbyte, GL_BYTE)
  TYPE_ENUM(GLubyte, GL_UNSIGNED_BYTE)
  TYPE_ENUM(GLshort, GL_SHORT)
  TYPE_ENUM(GLushort, GL_UNSIGNED_SHORT)
  TYPE_ENUM(GLint, GL_INT)
  TYPE_ENUM(GLuint, GL_UNSIGNED_INT)
  TYPE_ENUM(GLfloat, GL_FLOAT)
  
  #ifdef GL_DOUBLE
  TYPE_ENUM(GLdouble, GL_DOUBLE)
  #endif
  
  #undef TYPE_ENUM
}

#endif
