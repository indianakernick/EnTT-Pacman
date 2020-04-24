//
//  uniforms.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_uniforms_hpp
#define engine_opengl_uniforms_hpp

#include <array>
#include <vector>
#include "opengl.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GL {
  //vectors

  #define VEC(NUM, TYPE, TYPE_CHAR, ...)                                        \
    inline void setUniform(const GLint location, const TYPE &value) {           \
      glUniform##NUM##TYPE_CHAR(location, __VA_ARGS__);                         \
      CHECK_OPENGL_ERROR();                                                     \
    }
  
  #define VEC1(TYPE, TYPE_CHAR)                                                 \
    VEC(1, TYPE, TYPE_CHAR, value)
  #define VEC2(TYPE, TYPE_CHAR)                                                 \
    VEC(2, glm::tvec2<TYPE>, TYPE_CHAR, value.x, value.y)
  #define VEC3(TYPE, TYPE_CHAR)                                                 \
    VEC(3, glm::tvec3<TYPE>, TYPE_CHAR, value.x, value.y, value.z)
  #define VEC4(TYPE, TYPE_CHAR)                                                 \
    VEC(4, glm::tvec4<TYPE>, TYPE_CHAR, value.x, value.y, value.z, value.w)
  
  #define VEC_ALL(TYPE, TYPE_CHAR)                                              \
    VEC1(TYPE, TYPE_CHAR)                                                       \
    VEC2(TYPE, TYPE_CHAR)                                                       \
    VEC3(TYPE, TYPE_CHAR)                                                       \
    VEC4(TYPE, TYPE_CHAR)
  
  VEC_ALL(bool, i)
  VEC_ALL(GLfloat, f)
  VEC_ALL(GLint, i)
  VEC_ALL(GLuint, ui)
  #ifdef GL_DOUBLE
  VEC_ALL(GLdouble, d)
  #endif
  
  #undef VEC
  #undef VEC1
  #undef VEC2
  #undef VEC3
  #undef VEC4
  #undef VEC_ALL
  
  //matricies
  
  #define MAT(ROWS, COLUMNS, TYPE, TYPE_CHAR)                                   \
    inline void setUniform(                                                     \
      const GLint location,                                                     \
      const glm::tmat##ROWS##x##COLUMNS<TYPE> &value                            \
    ) {                                                                         \
      glUniformMatrix##ROWS##x##COLUMNS##TYPE_CHAR##v(                          \
        location, 1, GL_FALSE, glm::value_ptr(value)                            \
      );                                                                        \
      CHECK_OPENGL_ERROR();                                                     \
    }
  #define SQUARE_MAT(ROWS, TYPE, TYPE_CHAR)                                     \
    inline void setUniform(                                                     \
      const GLint location,                                                     \
      const glm::tmat##ROWS##x##ROWS<TYPE> &value                               \
    ) {                                                                         \
      glUniformMatrix##ROWS##TYPE_CHAR##v(                                      \
        location, 1, GL_FALSE, glm::value_ptr(value)                            \
      );                                                                        \
      CHECK_OPENGL_ERROR();                                                     \
    }
  
  #define MAT_ALL(TYPE, TYPE_CHAR)                                              \
    SQUARE_MAT(2, TYPE, TYPE_CHAR)                                              \
    MAT(2, 3, TYPE, TYPE_CHAR)                                                  \
    MAT(2, 4, TYPE, TYPE_CHAR)                                                  \
    MAT(3, 2, TYPE, TYPE_CHAR)                                                  \
    SQUARE_MAT(3, TYPE, TYPE_CHAR)                                              \
    MAT(3, 4, TYPE, TYPE_CHAR)                                                  \
    MAT(4, 2, TYPE, TYPE_CHAR)                                                  \
    MAT(4, 3, TYPE, TYPE_CHAR)                                                  \
    SQUARE_MAT(4, TYPE, TYPE_CHAR)
  
  MAT_ALL(GLfloat, f)
  #ifdef GL_DOUBLE
  MAT_ALL(GLdouble, d)
  #endif
  
  #undef MAT
  #undef SQUARE_MAT
  #undef MAT_ALL
  
  //arrays of vectors
  
  template <typename T>
  inline void setUniform(const GLint location, const std::vector<T> &values) {
    setUniform(location, values.size(), values.data());
  }
  
  template <typename T, size_t SIZE>
  inline void setUniform(const GLint location, const std::array<T, SIZE> &values) {
    setUniform(location, SIZE, values.data());
  }
  
  template <typename T, size_t SIZE>
  inline void setUniform(const GLint location, const T (&values)[SIZE]) {
    setUniform(location, SIZE, values);
  }
  
  #define VEC_ARRAY(NUM, TYPE, TYPE_CHAR, ARG)                                  \
    inline void setUniform(                                                     \
      const GLint location,                                                     \
      const size_t count,                                                       \
      const TYPE *const values                                                  \
    ) {                                                                         \
      assert(count > 0);                                                        \
      assert(values != nullptr);                                                \
      glUniform##NUM##TYPE_CHAR##v(location, static_cast<GLsizei>(count), ARG); \
      CHECK_OPENGL_ERROR();                                                     \
    }
  
  #define VEC1_ARRAY(TYPE, TYPE_CHAR)                                           \
    VEC_ARRAY(1, TYPE, TYPE_CHAR, values)
  #define VEC2_ARRAY(TYPE, TYPE_CHAR)                                           \
    VEC_ARRAY(2, glm::tvec2<TYPE>, TYPE_CHAR, glm::value_ptr(values[0]))
  #define VEC3_ARRAY(TYPE, TYPE_CHAR)                                           \
    VEC_ARRAY(3, glm::tvec3<TYPE>, TYPE_CHAR, glm::value_ptr(values[0]))
  #define VEC4_ARRAY(TYPE, TYPE_CHAR)                                           \
    VEC_ARRAY(4, glm::tvec4<TYPE>, TYPE_CHAR, glm::value_ptr(values[0]))
  
  #define VEC_ARRAY_ALL(TYPE, TYPE_CHAR)                                        \
    VEC1_ARRAY(TYPE, TYPE_CHAR)                                                 \
    VEC2_ARRAY(TYPE, TYPE_CHAR)                                                 \
    VEC3_ARRAY(TYPE, TYPE_CHAR)                                                 \
    VEC4_ARRAY(TYPE, TYPE_CHAR)
  
  VEC_ARRAY_ALL(GLfloat, f)
  VEC_ARRAY_ALL(GLint, i)
  VEC_ARRAY_ALL(GLuint, ui)
  #ifdef GL_DOUBLE
  VEC_ARRAY_ALL(GLdouble, d)
  #endif
  
  #undef VEC_ARRAY
  #undef VEC1_ARRAY
  #undef VEC2_ARRAY
  #undef VEC3_ARRAY
  #undef VEC4_ARRAY
  #undef VEC_ARRAY_ALL
  
  //arrays of matricies
  
  #define MAT_ARRAY(ROWS, COLUMNS, TYPE, TYPE_CHAR)                             \
    inline void setUniform(                                                     \
      const GLint location,                                                     \
      const size_t count,                                                       \
      const glm::tmat##ROWS##x##COLUMNS<TYPE> *const values                     \
    ) {                                                                         \
      assert(count > 0);                                                        \
      assert(values != nullptr);                                                \
      glUniformMatrix##ROWS##x##COLUMNS##TYPE_CHAR##v(                          \
        location, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0])\
      );                                                                        \
      CHECK_OPENGL_ERROR();                                                     \
    }
  #define SQUARE_MAT_ARRAY(ROWS, TYPE, TYPE_CHAR)                               \
    inline void setUniform(                                                     \
      const GLint location,                                                     \
      const size_t count,                                                       \
      const glm::tmat##ROWS##x##ROWS<TYPE> *const values                        \
    ) {                                                                         \
      assert(count > 0);                                                        \
      assert(values != nullptr);                                                \
      glUniformMatrix##ROWS##TYPE_CHAR##v(                                      \
        location, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0])\
      );                                                                        \
      CHECK_OPENGL_ERROR();                                                     \
    }
  
  #define MAT_ARRAY_ALL(TYPE, TYPE_CHAR)                                        \
    SQUARE_MAT_ARRAY(2, TYPE, TYPE_CHAR)                                        \
    MAT_ARRAY(2, 3, TYPE, TYPE_CHAR)                                            \
    MAT_ARRAY(2, 4, TYPE, TYPE_CHAR)                                            \
    MAT_ARRAY(3, 2, TYPE, TYPE_CHAR)                                            \
    SQUARE_MAT_ARRAY(3, TYPE, TYPE_CHAR)                                        \
    MAT_ARRAY(3, 4, TYPE, TYPE_CHAR)                                            \
    MAT_ARRAY(4, 2, TYPE, TYPE_CHAR)                                            \
    MAT_ARRAY(4, 3, TYPE, TYPE_CHAR)                                            \
    SQUARE_MAT_ARRAY(4, TYPE, TYPE_CHAR)
  
  MAT_ARRAY_ALL(GLfloat, f)
  #ifdef GL_DOUBLE
  MAT_ARRAY_ALL(GLdouble, d)
  #endif
  
  #undef MAT_ARRAY
  #undef SQUARE_MAT_ARRAY
  #undef MAT_ARRAY_ALL
}

#endif
