//
//  shader program.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_shader_program_hpp
#define engine_opengl_shader_program_hpp

#include "shader.hpp"

namespace GL {
  namespace detail {
    void deleteProgram(GLuint);
  }

  class ShaderProgram {
  public:
    UTILS_RAII_CLASS_FULL(ShaderProgram, GLuint, id, detail::deleteProgram)
    
    bool link() const;
    bool validate() const;
    void validateAndLog() const;
    void use() const;
    template <GLenum TYPE>
    void attach(const Shader<TYPE> &) const;
    void attach(GLuint) const;
    template <GLenum TYPE>
    void detach(const Shader<TYPE> &) const;
    void detach(GLuint) const;
    
    GLint getUniformLoc(const GLchar *) const;
    
    friend std::ostream &operator<<(std::ostream &, const ShaderProgram &);
    
  private:
    GLuint id;
  };
  
  std::ostream &operator<<(std::ostream &, const ShaderProgram &);
  
  void unuseProgram();
  
  ShaderProgram makeShaderProgram();
  
  template <GLenum ...TYPES>
  ShaderProgram makeShaderProgram(const Shader<TYPES> &... shaders) {
    ShaderProgram program = makeShaderProgram();
    [[maybe_unused]]
    const int dummy0[] = {(program.attach(shaders), 0)...};
    if (!program.link()) {
      std::cerr << "Failed to link shader program\n";
    }
    [[maybe_unused]]
    const int dummy1[] = {(program.detach(shaders), 0)...};
    std::cerr << "Shader program info log:\n" << program << '\n';
    return program;
  }

  template <typename ...Shaders>
  std::enable_if_t<
    sizeof...(Shaders) != 0
      && (std::is_base_of_v<std::istream, Shaders> && ...),
    ShaderProgram
  >
  makeShaderProgram(const Shaders &... streams) {
    return makeShaderProgram(makeShader(streams)...);
  }
}

#include "shader program.inl"

#endif
