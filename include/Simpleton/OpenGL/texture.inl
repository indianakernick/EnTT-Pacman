//
//  texture.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline void GL::detail::deleteTexture(const GLuint &id) {
  glDeleteTextures(1, &id);
  
  CHECK_OPENGL_ERROR();
}

template <GLenum TARGET>
void GL::unbindTexture(const int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  CHECK_OPENGL_ERROR();
  glBindTexture(TARGET, 0);
  CHECK_OPENGL_ERROR();
}

inline void GL::unbindTexture2D(const int unit) {
  unbindTexture<GL_TEXTURE_2D>(unit);
}

inline void GL::TexParams2D::setWrap(const GLint wrap) {
  wrapS = wrap;
  wrapT = wrap;
}

inline void GL::TexParams2D::setFilter(const GLint filter) {
  minFilter = filter;
  magFilter = filter;
}

template <GLenum TARGET>
GL::Texture<TARGET> GL::makeTexture() {
  GLuint id;
  glGenTextures(1, &id);
  CHECK_OPENGL_ERROR();
  return Texture<TARGET>(id);
}

inline GL::Texture2D GL::makeTexture2D() {
  return makeTexture<GL_TEXTURE_2D>();
}

inline void GL::setTexParams(const TexParams2D &params) {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrapS);
  CHECK_OPENGL_ERROR();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrapT);
  CHECK_OPENGL_ERROR();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.minFilter);
  CHECK_OPENGL_ERROR();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.magFilter);
  CHECK_OPENGL_ERROR();
}

inline void GL::setTexImage(const Image2D &image) {
  glPixelStorei(GL_UNPACK_ROW_LENGTH, image.pitch);

  CHECK_OPENGL_ERROR();
  
  glTexImage2D(
    GL_TEXTURE_2D,                            // target
    0,                                        // LOD
    image.alpha ? GL_SRGB8_ALPHA8 : GL_SRGB8, // internal format
    image.width,                              // width
    image.height,                             // height
    0,                                        // border
    image.alpha ? GL_RGBA : GL_RGB,           // format
    GL_UNSIGNED_BYTE,                         // type
    image.data                                // pixels
  );
  
  CHECK_OPENGL_ERROR();
  
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  
  CHECK_OPENGL_ERROR();
}

inline GL::Texture2D GL::makeTexture2D(
  const Image2D &image,
  const TexParams2D &params,
  const int unit
) {
  Texture2D texture = makeTexture2D();
  texture.bind(unit);
  setTexParams(params);
  setTexImage(image);
  return texture;
}
