//
//  opengl.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_opengl_hpp
#define engine_opengl_opengl_hpp

#include <cassert>
#include <iostream>
#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN

#include <GLES3/gl32.h>

#else

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#endif // EMSCRIPTEN

#if defined(DISABLE_OPENGL_ERROR_CHECKING) || !defined(GL_NO_ERROR)

#define CHECK_OPENGL_ERROR()

#else

namespace GL::detail {
  inline const char *glErrorString(const GLenum error) {
    switch (error) {
      case GL_NO_ERROR:
        return "No error";
      
      #ifdef GL_INVALID_ENUM
      case GL_INVALID_ENUM:
        return "Invalid enum";
      #endif
      
      #ifdef GL_INVALID_VALUE
      case GL_INVALID_VALUE:
        return "Invalid value";
      #endif
      
      #ifdef GL_INVALID_OPERATION
      case GL_INVALID_OPERATION:
        return "Invalid operation";
      #endif
      
      #ifdef GL_STACK_OVERFLOW
      case GL_STACK_OVERFLOW:
        return "Stack overflow";
      #endif
      
      #ifdef GL_STACK_UNDERFLOW
      case GL_STACK_UNDERFLOW:
        return "Stack underflow";
      #endif
      
      #ifdef GL_OUT_OF_MEMORY
      case GL_OUT_OF_MEMORY:
        return "Out of memory";
      #endif
      
      #ifdef GL_INVALID_FRAMEBUFFER_OPERATION
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "Invalid framebuffer operation";
      #endif
      
      #ifdef GL_CONTEXT_LOST
      case GL_CONTEXT_LOST:
        return "Context lost";
      #endif
      
      default:
        assert(false);
        return "(Unknown error)";
    }
  }
}

#define CHECK_OPENGL_ERROR()                                                    \
  do {                                                                          \
    int errorCount = 0;                                                         \
    for (GLenum error; (error = glGetError()) != GL_NO_ERROR; ++errorCount) {   \
      std::cerr << "OpenGL error: " << GL::detail::glErrorString(error) << '\n';\
    }                                                                           \
    assert(errorCount == 0);                                                    \
  } while (false)

#endif // DISABLE_OPENGL_ERROR_CHECKING

#endif
