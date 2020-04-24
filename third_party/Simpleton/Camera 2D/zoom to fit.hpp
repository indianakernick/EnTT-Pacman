//
//  zoom to fit.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_zoom_to_fit_hpp
#define engine_camera_2d_zoom_to_fit_hpp

#include "target.hpp"

namespace Cam2D {
  class ZoomToFit final : public Target<PropID::ZOOM> {
  public:
    ZoomToFit() = default;
    explicit ZoomToFit(glm::vec2);
    
    void setSize(glm::vec2);
    
    float calcTarget(Props, Params) override;
    
  private:
    glm::vec2 box = {1.0f, 1.0f};
  };
}

#include "zoom to fit.inl"

#endif
