//
//  shader.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_shader_hpp
#define engine_opengl_shader_hpp

#include <iostream>
#include "opengl.hpp"
#include "../Utils/generic raii.hpp"
#include "../Utils/function alias.hpp"

namespace GL {
  namespace detail {
    void deleteShader(GLuint);
  }

  template <GLenum TYPE_>
  class Shader {
  public:
    UTILS_RAII_CLASS_FULL(Shader, GLuint, id, detail::deleteShader)
  
    static constexpr GLenum TYPE = TYPE_;
  
    template <size_t... SIZES>
    void uploadSource(const GLchar (&... sources)[SIZES]) const {
      const GLchar *ptrs[] = {sources...};
      const GLint sizes[] = {static_cast<GLint>(SIZES - 1)...};
      glShaderSource(id, sizeof...(SIZES), ptrs, sizes);
      CHECK_OPENGL_ERROR();
    }
  
    void uploadSource(const GLchar *, size_t) const;
    bool compile() const;
    void compileAndLog() const;
  
    template <GLenum TYPE>
    friend std::ostream &operator<<(std::ostream &, const Shader<TYPE> &);
    
  private:
    GLuint id;
  };
  
  using VertShader = Shader<GL_VERTEX_SHADER>;
  using FragShader = Shader<GL_FRAGMENT_SHADER>;
  
  template <GLenum TYPE>
  struct ShaderName {};
  
  template <>
  struct ShaderName<GL_VERTEX_SHADER> {
    constexpr static const char *const value = "vertex";
  };
  
  template <>
  struct ShaderName<GL_FRAGMENT_SHADER> {
    constexpr static const char *const value = "fragment";
  };
  
  template <GLenum TYPE>
  std::ostream &operator<<(std::ostream &, const Shader<TYPE> &);
  template <GLenum TYPE>
  std::istream &operator>>(std::istream &, const Shader<TYPE> &);
  
  template <GLenum TYPE>
  Shader<TYPE> makeShader();
  template <GLenum TYPE>
  Shader<TYPE> makeShader(const GLchar *, size_t);
  template <GLenum TYPE>
  Shader<TYPE> makeShader(std::istream &);
  template <GLenum TYPE, size_t... SIZES>
  Shader<TYPE> makeShader(const GLchar (&... sources)[SIZES]);
  
  FUN_ALIAS(makeVertShader, makeShader<GL_VERTEX_SHADER>)
  FUN_ALIAS(makeFragShader, makeShader<GL_FRAGMENT_SHADER>)
}

#include "shader.inl"

#endif
