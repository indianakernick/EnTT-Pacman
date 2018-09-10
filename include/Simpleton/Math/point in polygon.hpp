//
//  point in polygon.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_point_in_polygon_hpp
#define engine_math_point_in_polygon_hpp

#include <vector>
#include <glm/vec2.hpp>

namespace Math {
  ///Determine whether a point is within a polygon
  template <typename T>
  bool pointInPolygon(const glm::tvec2<T> test, const std::vector<glm::tvec2<T>> &vert) {
    return pointInPolygon(test, vert.size(), vert.data());
  }

  ///Determine whether a point is within a polygon
  template <typename T>
  bool pointInPolygon(const glm::tvec2<T> test, const size_t nvert, const glm::tvec2<T> *vert) {
    //http://stackoverflow.com/a/2922778
    
    bool c = false;
    for (size_t i = 0, j = nvert - 1; i < nvert; j = i++) {
      if (
        (vert[i].y > test.y != vert[j].y > test.y) &&
        (test.x < (vert[j].x - vert[i].x) * (test.y - vert[i].y) / (vert[j].y - vert[i].y) + vert[i].x)
      ) {
        c = !c;
      }
    }
    return c;
  }
}

#endif
