//
//  buffer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline void GL::detail::deleteBuffer(const GLuint &id) {
  glDeleteBuffers(1, &id);
  
  CHECK_OPENGL_ERROR();
}

template <GLenum TARGET>
void GL::unbindBuffer() {
  glBindBuffer(TARGET, 0);
  
  CHECK_OPENGL_ERROR();
}

inline void GL::unbindArrayBuffer() {
  unbindBuffer<GL_ARRAY_BUFFER>();
}

inline void GL::unbindElementBuffer() {
  unbindBuffer<GL_ELEMENT_ARRAY_BUFFER>();
}

template <GLenum TARGET>
GL::Buffer<TARGET> GL::makeBuffer() {
  GLuint id;
  glGenBuffers(1, &id);
  CHECK_OPENGL_ERROR();
  return Buffer<TARGET>(id);
}

template <GLenum TARGET>
GL::Buffer<TARGET> GL::makeBuffer(const size_t size, const GLenum usage) {
  return makeBuffer<TARGET>(nullptr, size, usage);
}

template <GLenum TARGET>
GL::Buffer<TARGET> GL::makeBuffer(
  const GLvoid *data,
  const size_t size,
  const GLenum usage
) {
  Buffer<TARGET> buffer = makeBuffer<TARGET>();
  buffer.bind();
  glBufferData(TARGET, static_cast<GLsizeiptr>(size), data, usage);
  CHECK_OPENGL_ERROR();
  return buffer;
}
