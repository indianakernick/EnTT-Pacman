//
//  static char buffer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 20/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_static_char_buffer_hpp
#define engine_opengl_static_char_buffer_hpp

#include <memory>
#include "opengl.hpp"

namespace GL {
  namespace detail {
    inline GLchar *getCharBuf(const GLint minSize) {
      static GLint bufSize = 1024;
      static auto bufData = std::make_unique<GLchar []>(bufSize);
      if (bufSize < minSize) {
        bufSize = minSize * 2;
        bufData = std::make_unique<GLchar []>(bufSize);
      }
      return bufData.get();
    }
  }
}

#endif
