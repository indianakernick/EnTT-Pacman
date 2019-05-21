//
//  renderer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "shaders.hpp"

#include "load surface.hpp"
#include "../OpenGL/uniforms.hpp"
#include "../OpenGL/attrib pointer.hpp"

inline void G2D::Renderer::init() {
  #ifdef EMSCRIPTEN
  initImpl(ES_SHADER_VERSION);
  #else
  initImpl(CORE_SHADER_VERSION);
  #endif
}

inline void G2D::Renderer::quit() {
  elemBuf.reset();
  arrayBuf.reset();
  vertArray.reset();
  program.reset();
  textures.clear();
}

inline G2D::TextureID G2D::Renderer::addTexture(GL::Texture2D &&texture) {
  const TextureID id = textures.size();
  textures.emplace_back(std::move(texture));
  return id;
}

inline G2D::TextureID G2D::Renderer::addTexture(
  const Surface &surface,
  const TexParams params
) {
  assert(surface.bytesPerPixel() == 3 || surface.bytesPerPixel() == 4);
  
  const GL::Image2D glImage {
    surface.data(),
    static_cast<GLsizei>(surface.width()),
    static_cast<GLsizei>(surface.height()),
    static_cast<GLint>(surface.pitch() / surface.bytesPerPixel()),
    surface.bytesPerPixel() == 4
  };
  const GL::TexParams2D glParams {
    params.wrap == TexWrap::REPEAT ? GL_REPEAT : GL_CLAMP_TO_EDGE,
    params.wrap == TexWrap::REPEAT ? GL_REPEAT : GL_CLAMP_TO_EDGE,
    params.min == MinFilter::NEAREST ? GL_NEAREST : GL_LINEAR,
    params.mag == MagFilter::NEAREST ? GL_NEAREST : GL_LINEAR
  };
  return addTexture(GL::makeTexture2D(glImage, glParams, 0));
}

inline G2D::TextureID G2D::Renderer::addTexture(
  const std::string_view path,
  const TexParams params
) {
  return addTexture(loadSurfaceRGBA(path), params);
}

inline bool G2D::Renderer::resizeQuadBuf(const size_t quads) {
  if (quads > numQuads) {
    setQuadBufSize(quads);
    return true;
  }
  return false;
}

inline bool G2D::Renderer::writeQuads(const QuadRange range, const Quad *quads) {
  const bool resized = range.end > numQuads;
  if (resized) {
    setQuadBufSize(range.end);
  }
  if (quads == nullptr) {
    return resized;
  }
  
  arrayBuf.bind();
  glBufferSubData(
    GL_ARRAY_BUFFER,
    sizeof(Quad) * range.begin,
    sizeof(Quad) * range.size(),
    quads
  );
  CHECK_OPENGL_ERROR();
  GL::unbindArrayBuffer();
  
  return resized;
}

inline void G2D::Renderer::render(const QuadRange range, const RenderParams &params) {
  vertArray.bind();
  program.use();
  
  GL::setUniform(viewProjLoc, params.viewProj);
  textures.at(params.tex).bind(0);
  
  program.validateAndLog();
  
  glDrawElements(
    GL_TRIANGLES,
    static_cast<GLsizei>(QUAD_INDICIES * range.size()),
    GL::TypeEnum<ElemType>::type,
    reinterpret_cast<GLvoid *>(QUAD_ELEM_SIZE * range.begin)
  );
  CHECK_OPENGL_ERROR();
  
  GL::unbindTexture2D(0);
  GL::unuseProgram();
  GL::unbindVertexArray();
}

inline void G2D::Renderer::initState() {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  CHECK_OPENGL_ERROR();
}

inline void G2D::Renderer::initUniforms() {
  viewProjLoc = program.getUniformLoc("viewProj");
  texLoc = program.getUniformLoc("tex");
  
  program.use();
  GL::setUniform(texLoc, 0);
  GL::unuseProgram();
}

inline void G2D::Renderer::initVertexArray() {
  vertArray = GL::makeVertexArray();
  vertArray.bind();
  
  arrayBuf = GL::makeArrayBuffer(size_t(0), GL_DYNAMIC_DRAW);
  elemBuf = GL::makeElementBuffer(size_t(0), GL_STATIC_DRAW);
  
  GL::attribs<Attribs>();
  
  GL::unbindVertexArray();
}

inline void G2D::Renderer::fillIndicies(const size_t minQuads) {
  if (indicies.size() < minQuads * QUAD_INDICIES) {
    indicies.reserve(minQuads * QUAD_INDICIES);
    ElemType index = indicies.size() / QUAD_INDICIES * QUAD_VERTS;
    const ElemType lastIndex = minQuads * QUAD_VERTS;
    for (; index != lastIndex; index += QUAD_VERTS) {
      indicies.push_back(index + 0);
      indicies.push_back(index + 1);
      indicies.push_back(index + 2);
      indicies.push_back(index + 2);
      indicies.push_back(index + 3);
      indicies.push_back(index + 0);
    }
  }
}

inline void G2D::Renderer::setQuadBufSize(const size_t quads) {
  numQuads = quads;
  fillIndicies(numQuads);
  
  arrayBuf.bind();
  glBufferData(GL_ARRAY_BUFFER, numQuads * QUAD_ATTR_SIZE, nullptr, GL_DYNAMIC_DRAW);
  CHECK_OPENGL_ERROR();
  GL::unbindArrayBuffer();
  
  elemBuf.bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numQuads * QUAD_ELEM_SIZE, indicies.data(), GL_STATIC_DRAW);
  CHECK_OPENGL_ERROR();
  GL::unbindElementBuffer();
}

template <size_t SIZE>
inline void G2D::Renderer::initImpl(const char (&version)[SIZE]) {
  initState();
  program = GL::makeShaderProgram(
    GL::makeVertShader(version, VERT_SHADER),
    GL::makeFragShader(version, FRAG_SHADER)
  );
  initUniforms();
  initVertexArray();
}
