//
//  shader program.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static char buffer.hpp"

inline void GL::detail::deleteProgram(const GLuint id) {
  glDeleteProgram(id);
  
  CHECK_OPENGL_ERROR();
}

inline bool GL::ShaderProgram::link() const {
  glLinkProgram(id);
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  CHECK_OPENGL_ERROR();
  return status == GL_TRUE;
}

inline bool GL::ShaderProgram::validate() const {
  glValidateProgram(id);
  GLint status;
  glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
  CHECK_OPENGL_ERROR();
  return status == GL_TRUE;
}

inline void GL::ShaderProgram::validateAndLog() const {
  if (!validate()) {
    std::cerr << "Failed to validate program\n";
    std::cerr << "Shader program info log:\n" << (*this) << '\n';
  }
}

inline void GL::ShaderProgram::use() const {
  glUseProgram(id);
  
  CHECK_OPENGL_ERROR();
}

template <GLenum TYPE>
void GL::ShaderProgram::attach(const Shader<TYPE> &shader) const {
  attach(shader.get());
}

inline void GL::ShaderProgram::attach(const GLuint shaderID) const {
  glAttachShader(id, shaderID);
  
  CHECK_OPENGL_ERROR();
}

template <GLenum TYPE>
void GL::ShaderProgram::detach(const Shader<TYPE> &shader) const {
  detach(shader.get());
}

inline void GL::ShaderProgram::detach(const GLuint shaderID) const {
  glDetachShader(id, shaderID);
  
  CHECK_OPENGL_ERROR();
}

inline GLint GL::ShaderProgram::getUniformLoc(const GLchar *name) const {
  const GLint location = glGetUniformLocation(id, name);
  assert(location != -1);
  CHECK_OPENGL_ERROR();
  return location;
}

inline std::ostream &GL::operator<<(std::ostream &stream, const GL::ShaderProgram &program) {
  GLint logLength;
  glGetProgramiv(program.id, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength) {
    GLchar *const buf = detail::getCharBuf(logLength);
    glGetProgramInfoLog(program.id, logLength, nullptr, buf);
    stream << std::string_view(buf, logLength);
  }

  CHECK_OPENGL_ERROR();
  
  return stream;
}

inline void GL::unuseProgram() {
  glUseProgram(0);
  CHECK_OPENGL_ERROR();
}

inline GL::ShaderProgram GL::makeShaderProgram() {
  ShaderProgram program(glCreateProgram());
  CHECK_OPENGL_ERROR();
  return program;
}
