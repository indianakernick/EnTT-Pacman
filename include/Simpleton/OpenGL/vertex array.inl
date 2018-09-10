//
//  vertex array.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline void GL::detail::deleteVertexArray(const GLuint &id) {
  glDeleteVertexArrays(1, &id);
  
  CHECK_OPENGL_ERROR();
}

inline void GL::VertexArray::bind() const {
  glBindVertexArray(id);
  
  CHECK_OPENGL_ERROR();
}

inline void GL::unbindVertexArray() {
  glBindVertexArray(0);
  
  CHECK_OPENGL_ERROR();
}

inline GL::VertexArray GL::makeVertexArray() {
  GLuint id;
  glGenVertexArrays(1, &id);
  CHECK_OPENGL_ERROR();
  return VertexArray(id);
}
