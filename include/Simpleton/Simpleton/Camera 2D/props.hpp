//
//  props.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_props_hpp
#define engine_camera_2d_props_hpp

#include <glm/vec2.hpp>

namespace Cam2D {
  /// Properties that define the camera's current state
  struct Props {
    ///Position in meters of the camera
    glm::vec2 pos = {0.0f, 0.0f};
    ///Scale factor (zoom)
    float scale = 1.0f;
    ///Angle in radians
    float angle = 0.0f;
  };
  
  /// Parameters that influence the change of the camera's current state
  struct Params {
    ///Aspect ratio of the window
    float aspect;
    ///Time in seconds since the last update
    float delta;
  };
  
  enum class PropID {
    POS,
    ZOOM,
    ANGLE
  };
  
  template <PropID>
  struct PropTraits;
  
  template <>
  struct PropTraits<PropID::POS> {
    using type = glm::vec2;
    static constexpr auto PTR = &Props::pos;
  };
  
  template <>
  struct PropTraits<PropID::ZOOM> {
    using type = float;
    static constexpr auto PTR = &Props::scale;
  };
  
  template <>
  struct PropTraits<PropID::ANGLE> {
    using type = float;
    static constexpr auto PTR = &Props::angle;
  };
  
  template <PropID PROP>
  using PropType = typename PropTraits<PROP>::type;
  
  template <PropID PROP>
  constexpr PropType<PROP> &getProp(Props &props) {
    return props.*PropTraits<PROP>::PTR;
  }
  
  template <PropID PROP>
  constexpr const PropType<PROP> &getProp(const Props &props) {
    return props.*PropTraits<PROP>::PTR;
  }
}

#endif
