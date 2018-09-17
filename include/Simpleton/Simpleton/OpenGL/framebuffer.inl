//
//  framebuffer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 23/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "framebuffer.hpp"

inline void GL::detail::deleteFramebuffer(const GLuint &id) {
  glDeleteFramebuffers(1, &id);
  
  CHECK_OPENGL_ERROR();
}

inline void GL::Framebuffer::bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  
  CHECK_OPENGL_ERROR();
}

inline bool GL::Framebuffer::checkStatus() const {
  const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  CHECK_OPENGL_ERROR();
  
  if (status == GL_FRAMEBUFFER_COMPLETE) {
    return true;
  } else if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
    std::cerr << "Framebuffer has an incomplete attachment\n";
  } else if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
    std::cerr << "Framebuffer is missing attachments\n";
  } else if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
    std::cerr << "Framebuffer configuration is unsupported\n";
  } else {
    std::cerr << "Framebuffer has an unknown status\n";
  }
  
  return false;
}

inline void GL::Framebuffer::attachColor(
  const Texture2D &texture,
  const size_t index
) const {
  glFramebufferTexture2D(
    GL_FRAMEBUFFER,
    GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(index),
    GL_TEXTURE_2D,
    texture.get(),
    0
  );
  
  CHECK_OPENGL_ERROR();
}

inline GL::Framebuffer GL::makeFramebuffer() {
  GLuint id;
  glGenFramebuffers(1, &id);
  CHECK_OPENGL_ERROR();
  return Framebuffer(id);
}

inline GL::Framebuffer GL::makeDefaultFramebuffer() {
  return Framebuffer(GLuint(0));
}

inline void GL::bindDefaultFramebuffer() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  CHECK_OPENGL_ERROR();
}
