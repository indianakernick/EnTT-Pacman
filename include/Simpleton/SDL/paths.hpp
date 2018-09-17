//
//  paths.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_paths_hpp
#define engine_sdl_paths_hpp

#include <string>
#include <string_view>

namespace SDL {
  std::string getSaveDir(std::string_view companyName, std::string_view appName);
  std::string getResDir();
  std::string res(const std::string &);
}

#include "paths.inl"

#endif
