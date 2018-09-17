//
//  transform.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_transform_hpp
#define engine_camera_2d_transform_hpp

#include "aabb.hpp"
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

namespace Cam2D {
  struct Props;
  
  enum class Origin {
    TOP_LEFT,
    TOP_MID,
    TOP_RIGHT,
    MID_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_MID,
    BOTTOM_LEFT,
    MID_LEFT,
    CENTER
  };
  
  class Transform {
  public:
    Transform() = default;
    
    void setOrigin(Origin);
    void setInvertX(bool);
    void setInvertY(bool);
    void setSize(glm::vec2);
    
    glm::mat3 toPixels() const;
    glm::mat3 toMeters() const;
    
    void calculate(Props, Params);
    
  private:
    glm::mat3 toPixelsMat;
    glm::mat3 toMetersMat;
    glm::vec2 boxSize = {0.0f, 0.0f};
    Origin origin = Origin::CENTER;
    bool invertX = false;
    bool invertY = false;
    
    glm::vec2 calcOriginPos() const;
    glm::vec2 calcInvertedScale() const;
    glm::vec2 calcShiftedPos(Params) const;
  };
}

#include "transform.inl"

#endif
