//
//  target.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 26/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_target_hpp
#define engine_camera_2d_target_hpp

#include "props.hpp"

namespace Cam2D {
  template <PropID PROP_>
  class Target {
  public:
    static constexpr PropID PROP = PROP_;
    using Type = PropType<PROP>;
  
    Target() = default;
    virtual ~Target() = default;
    
    virtual Type calcTarget(Props, Params) = 0;
  };
}

#endif
