//
//  rect.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_rect_hpp
#define engine_math_rect_hpp

#include <cmath>
#include <glm/vec2.hpp>
#include "../Grid/dir.hpp"

namespace Math {
  template <typename T, Grid::Dir POSITIVE_X, Grid::Dir POSITIVE_Y>
  struct RectPS;
  
  template <typename T, Grid::Dir POSITIVE_X, Grid::Dir POSITIVE_Y>
  struct RectCS;

  ///A rectangle defined by a minimum point and a maximum point
  template <typename T, Grid::Dir POSITIVE_X = Grid::Dir::right, Grid::Dir POSITIVE_Y = Grid::Dir::up>
  struct RectPP {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert(!sameAxis(POSITIVE_X, POSITIVE_Y));
    
    using Scalar = T;
    using Vector = glm::tvec2<Scalar>;
    static constexpr Grid::Dir PLUS_X = POSITIVE_X;
    static constexpr Grid::Dir PLUS_Y = POSITIVE_Y;
    static constexpr Scalar EPSILON = std::is_integral<Scalar>::value ? Scalar(1) : Scalar(0);
    
    static const RectPP NEG_INF;
    static const RectPP INF;
    
    RectPP()
      : min(Scalar(0), Scalar(0)), max(-EPSILON, -EPSILON) {}
    RectPP(const RectPP &) = default;
    RectPP(RectPP &&) = default;
    ~RectPP() = default;
    
    RectPP &operator=(const RectPP &) = default;
    RectPP &operator=(RectPP &&) = default;
    
    explicit RectPP(const Vector size)
      : min(Scalar(0), Scalar(0)), max(size - EPSILON) {}
    RectPP(const Vector min, const Vector max)
      : min(min), max(max) {}
    RectPP(const Scalar minx, const Scalar miny, const Scalar maxx, const Scalar maxy)
      : min(minx, miny), max(maxx, maxy) {}
    
    template <typename U>
    explicit RectPP(const RectPP<U, PLUS_X, PLUS_Y> other)
      : min(static_cast<Vector>(other.min)),
        max(static_cast<Vector>(other.max + RectPP<U, PLUS_X, PLUS_Y>::EPSILON) - EPSILON) {}
    
    template <typename U>
    explicit RectPP(const RectPS<U, PLUS_X, PLUS_Y> other)
      : min(static_cast<Vector>(other.min)),
        max(static_cast<Vector>(other.p + other.s) - EPSILON) {}
    
    template <typename U>
    explicit RectPP(const RectCS<U, PLUS_X, PLUS_Y> other)
      : min(static_cast<Vector>(other.c - other.h)),
        max(static_cast<Vector>(other.c + other.h) - EPSILON) {}
    
    bool operator==(const RectPP other) const {
      return min == other.min && max == other.max;
    }
    bool operator!=(const RectPP other) const {
      return min != other.min || max != other.max;
    }
    
    void setPoint(const Vector point) {
      min = point;
      max = point;
    }
    
    Scalar side(const Grid::Dir dir) const {
      switch (dir) {
        case PLUS_Y:
          return max.y;
        case PLUS_X:
          return max.x;
        case opposite(PLUS_Y):
          return min.y;
        case opposite(PLUS_X):
          return min.x;
        default:
          assert(false);
      }
    }
    
    void side(const Grid::Dir dir, const Scalar val) {
      switch (dir) {
        case PLUS_Y:
          max.y = val;
          break;
        case PLUS_X:
          max.x = val;
          break;
        case opposite(PLUS_Y):
          min.y = val;
          break;
        case opposite(PLUS_X):
          min.x = val;
          break;
        default:
          assert(false);
      }
    }
    
    Scalar top() const {
      return side(Grid::Dir::top);
    }
    Scalar right() const {
      return side(Grid::Dir::right);
    }
    Scalar bottom() const {
      return side(Grid::Dir::bottom);
    }
    Scalar left() const {
      return side(Grid::Dir::left);
    }
    
    void top(const Scalar val) {
      side(Grid::Dir::top, val);
    }
    void right(const Scalar val) {
      side(Grid::Dir::right, val);
    }
    void bottom(const Scalar val) {
      side(Grid::Dir::bottom, val);
    }
    void left(const Scalar val) {
      side(Grid::Dir::left, val);
    }
    
    Vector topLeft() const {
      return {side(Grid::Dir::left), side(Grid::Dir::top)};
    }
    Vector topRight() const {
      return {side(Grid::Dir::right), side(Grid::Dir::top)};
    }
    Vector bottomRight() const {
      return {side(Grid::Dir::right), side(Grid::Dir::bottom)};
    }
    Vector bottomLeft() const {
      return {side(Grid::Dir::left), side(Grid::Dir::bottom)};
    }
    
    void topLeft(const Vector val) {
      side(Grid::Dir::left, val.x);
      side(Grid::Dir::top, val.y);
    }
    void topRight(const Vector val) {
      side(Grid::Dir::right, val.x);
      side(Grid::Dir::top, val.y);
    }
    void bottomRight(const Vector val) {
      side(Grid::Dir::right, val.x);
      side(Grid::Dir::bottom, val.y);
    }
    void bottomLeft(const Vector val) {
      side(Grid::Dir::left, val.x);
      side(Grid::Dir::bottom, val.y);
    }
    
    Vector size() const {
      return (max - min) + EPSILON;
    }
    
    bool sizeZero() const {
      return (max.x - min.x) + EPSILON == Scalar(0) &&
             (max.y - min.y) + EPSILON == Scalar(0);
    }
    
    ///Enlarge the rectangle to enclose the point
    void extendToEnclose(const Vector point) {
      if (point.x < min.x) {
        min.x = point.x;
      } else if (point.x > max.x) {
        max.x = point.x;
      }
      
      if (point.y < min.y) {
        min.y = point.y;
      } else if (point.y > max.y) {
        max.y = point.y;
      }
    }
    
    bool interceptsWith(const RectPP other) const {
      return min.x           < other.max.x + EPSILON &&
             min.y           < other.max.y + EPSILON &&
             max.x + EPSILON > other.min.x           &&
             max.y + EPSILON > other.min.y;
    }
    bool encloses(const RectPP other) const {
      return min.x <= other.min.x &&
             min.y <= other.min.y &&
             max.x >= other.max.x &&
             max.y >= other.max.y;
    }
    bool encloses(const Vector other) const {
      return min.x <= other.x &&
             min.y <= other.y &&
             max.x >= other.x &&
             max.y >= other.y;
    }
    
    Vector min;
    Vector max;
  };
  
  template <typename T, Grid::Dir P_X, Grid::Dir P_Y>
  const RectPP<T, P_X, P_Y> RectPP<T, P_X, P_Y>::NEG_INF = {
    RectPP<T, P_X, P_Y>::Vector(std::numeric_limits<T>::max()),
    RectPP<T, P_X, P_Y>::Vector(std::numeric_limits<T>::lowest()),
  };
  
  template <typename T, Grid::Dir P_X, Grid::Dir P_Y>
  const RectPP<T, P_X, P_Y> RectPP<T, P_X, P_Y>::INF = {
    RectPP<T, P_X, P_Y>::Vector(std::numeric_limits<T>::lowest()),
    RectPP<T, P_X, P_Y>::Vector(std::numeric_limits<T>::max()),
  };
  
  ///A rectangle defined by a negative point and a size
  template <typename T, Grid::Dir POSITIVE_X = Grid::Dir::right, Grid::Dir POSITIVE_Y = Grid::Dir::up>
  struct RectPS {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert(!sameAxis(POSITIVE_X, POSITIVE_Y));
  
    using Scalar = T;
    using Vector = glm::tvec2<Scalar>;
  
    static constexpr Grid::Dir PLUS_X = POSITIVE_X;
    static constexpr Grid::Dir PLUS_Y = POSITIVE_Y;
    static constexpr Scalar EPSILON = std::is_integral<Scalar>::value ? Scalar(1) : Scalar(0);
    
    static const RectPS NEG_INF;
    static const RectPS INF;
  
    RectPS()
      : p(Scalar(0), Scalar(0)), s(Scalar(0), Scalar(0)) {}
    RectPS(const RectPS &) = default;
    RectPS(RectPS &&) = default;
    ~RectPS() = default;
    
    RectPS &operator=(const RectPS &) = default;
    RectPS &operator=(RectPS &&) = default;
    
    explicit RectPS(const Vector size)
      : p(Scalar(0), Scalar(0)), s(size) {}
    RectPS(const Vector pos, const Vector size)
      : p(pos), s(size) {}
    RectPS(const Scalar px, const Scalar py, const Scalar sx, const Scalar sy)
      : p(px, py), s(sx, sy) {}
    
    template <typename U>
    explicit RectPS(const RectPS<U, PLUS_X, PLUS_Y> other)
      : p(static_cast<Vector>(other.p)),
        s(static_cast<Vector>(other.s)) {}
    
    template <typename U>
    explicit RectPS(const RectPP<U, PLUS_X, PLUS_Y> other)
      : p(static_cast<Vector>(other.min)),
        s(static_cast<Vector>(other.size())) {}
    
    template <typename U>
    explicit RectPS(const RectCS<U, PLUS_X, PLUS_Y> other)
      : p(static_cast<Vector>(other.c - other.h)),
        s(static_cast<Vector>(other.h) * Scalar(2)) {}
    
    bool operator==(const RectPS other) const {
      return p == other.p && s == other.s;
    }
    bool operator!=(const RectPS other) const {
      return p != other.p || s != other.s;
    }
    
    void setPoint(const Vector point) {
      p = point;
      s = Vector(EPSILON);
    }
    
    Scalar side(const Grid::Dir dir) const {
      switch (dir) {
        case PLUS_Y:
          return p.y + s.y - EPSILON;
        case PLUS_X:
          return p.x + s.x - EPSILON;
        case opposite(PLUS_Y):
          return p.y;
        case opposite(PLUS_X):
          return p.x;
        default:
          assert(false);
      }
    }
    
    void side(const Grid::Dir dir, const Scalar val) {
      switch (dir) {
        case PLUS_Y:
          s.y = val - p.y + EPSILON;
          break;
        case PLUS_X:
          s.x = val - p.x + EPSILON;
          break;
        case opposite(PLUS_Y):
          p.y = val;
          break;
        case opposite(PLUS_X):
          p.x = val;
          break;
        default:
          assert(false);
      }
    }
    
    Scalar top() const {
      return side(Grid::Dir::top);
    }
    Scalar right() const {
      return side(Grid::Dir::right);
    }
    Scalar bottom() const {
      return side(Grid::Dir::bottom);
    }
    Scalar left() const {
      return side(Grid::Dir::left);
    }
    
    void top(const Scalar val) {
      side(Grid::Dir::top, val);
    }
    void right(const Scalar val) {
      side(Grid::Dir::right, val);
    }
    void bottom(const Scalar val) {
      side(Grid::Dir::bottom, val);
    }
    void left(const Scalar val) {
      side(Grid::Dir::left, val);
    }
    
    bool interceptsWith(const RectPS other) const {
      return p.x       < other.p.x + other.s.x &&
             p.y       < other.p.y + other.s.y &&
             p.x + s.x > other.p.x             &&
             p.y + s.y > other.p.y;
    }
    bool encloses(const RectPS other) const {
      return p.x       <= other.p.x             &&
             p.y       <= other.p.y             &&
             p.x + s.x >= other.p.x + other.s.x &&
             p.y + s.y >= other.p.y + other.s.y;
    }
    bool encloses(const Vector other) const {
      return p.x                 <= other.x &&
             p.y                 <= other.y &&
             p.x + s.x - EPSILON >= other.x &&
             p.y + s.y - EPSILON >= other.y;
    }
    
    union {
      Vector p;
      Vector pos;
    };
    union {
      Vector s;
      Vector size;
    };
  };
  
  template <typename T, Grid::Dir P_X, Grid::Dir P_Y>
  const RectPS<T, P_X, P_Y> RectPS<T, P_X, P_Y>::NEG_INF = {
    RectPS<T, P_X, P_Y>::Vector(std::numeric_limits<T>::max()),
    RectPS<T, P_X, P_Y>::Vector(std::numeric_limits<T>::lowest()),
  };
  
  template <typename T, Grid::Dir P_X, Grid::Dir P_Y>
  const RectPS<T, P_X, P_Y> RectPS<T, P_X, P_Y>::INF = {
    RectPS<T, P_X, P_Y>::Vector(std::numeric_limits<T>::lowest()),
    RectPS<T, P_X, P_Y>::Vector(std::numeric_limits<T>::max()),
  };
  
  ///A rectangle defined by a center and a half size
  template <typename T, Grid::Dir POSITIVE_X = Grid::Dir::right, Grid::Dir POSITIVE_Y = Grid::Dir::up>
  struct RectCS {
    /*
    Using integers for this format doesn't really work. The only way to make it
    work would be to assume that integer units don't have size. In RectPS and
    RectPP, a glm::tvec2<int> is really a rectangle with a size of one. This
    means that I have to add and subtract one (EPSILON) around the place to make
    sure everything is correct. A glm::tvec2<float> is a point with no size.
    
    This Rect has a few division by 2s and when you divide int(1) by int(2) you
    get int(0). There's just too much lossyness.
    */
  
    static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
    static_assert(!sameAxis(POSITIVE_X, POSITIVE_Y));
    
    using Scalar = T;
    using Vector = glm::tvec2<Scalar>;
    
    static constexpr Grid::Dir PLUS_X = POSITIVE_X;
    static constexpr Grid::Dir PLUS_Y = POSITIVE_Y;
    
    static const RectCS NEG_INF;
    static const RectCS INF;
    
    RectCS()
      : c(Scalar(0), Scalar(0)), h(Scalar(0), Scalar(0)) {}
    RectCS(const RectCS &) = default;
    RectCS(RectCS &&) = default;
    ~RectCS() = default;
    
    RectCS &operator=(const RectCS &) = default;
    RectCS &operator=(RectCS &&) = default;
    
    explicit RectCS(const Vector size)
      : c(Scalar(0), Scalar(0)), h(size / Scalar(2)) {}
    RectCS(const Vector center, const Vector size)
      : c(center), h(size / Scalar(2)) {}
    RectCS(const Scalar cx, const Scalar cy, const Scalar sx, const Scalar sy)
      : c(cx, cy), h(sx / Scalar(2), sy / Scalar(2)) {}
    
    template <typename U>
    explicit RectCS(const RectCS<U, PLUS_X, PLUS_Y> other)
      : c(static_cast<Vector>(other.c)),
        h(static_cast<Vector>(other.h)) {}
    
    template <typename U>
    explicit RectCS(const RectPP<U, PLUS_X, PLUS_Y> other) {
      h = static_cast<Vector>(other.size()) / Scalar(2);
      c = static_cast<Vector>(other.min) + h;
    }
    
    template <typename U>
    explicit RectCS(const RectPS<U, PLUS_X, PLUS_Y> other) {
      h = static_cast<Vector>(other.s) / Scalar(2);
      c = static_cast<Vector>(other.p) + h;
    }
    
    bool operator==(const RectCS other) const {
      return c == other.c && h == other.s;
    }
    bool operator!=(const RectCS other) const {
      return c != other.c || h != other.s;
    }
    
    void setPoint(const Vector point) {
      center = point;
      halfSize = Vector(Scalar(0));
    }
    
    Scalar side(const Grid::Dir dir) const {
      switch (dir) {
        case PLUS_Y:
          return c.y + h.y;
        case PLUS_X:
          return c.x + h.x;
        case opposite(PLUS_Y):
          return c.y - h.y;
        case opposite(PLUS_X):
          return c.x - h.x;
        default:
          assert(false);
      }
    }
    
    void side(const Grid::Dir dir, const Scalar val) {
      switch (dir) {
        case PLUS_Y: {
          const float delta = (val - c.y - h.y) / Scalar(2);
          c.y += delta;
          h.y += delta;
          break;
        }
        case PLUS_X: {
          const float delta = (val - c.x - h.x) / Scalar(2);
          c.x += delta;
          h.x += delta;
          break;
        }
        case opposite(PLUS_Y): {
          const float delta = (val - c.y + h.y) / Scalar(2);
          c.y += delta;
          h.y += delta;
          break;
        }
        case opposite(PLUS_X): {
          const float delta = (val - c.x + h.x) / Scalar(2);
          c.x += delta;
          h.x += delta;
          break;
        }
        default:
          assert(false);
      }
    }
    
    Scalar top() const {
      return side(Grid::Dir::top);
    }
    Scalar right() const {
      return side(Grid::Dir::right);
    }
    Scalar bottom() const {
      return side(Grid::Dir::bottom);
    }
    Scalar left() const {
      return side(Grid::Dir::left);
    }
    
    void top(const Scalar val) {
      side(Grid::Dir::top, val);
    }
    void right(const Scalar val) {
      side(Grid::Dir::right, val);
    }
    void bottom(const Scalar val) {
      side(Grid::Dir::bottom, val);
    }
    void left(const Scalar val) {
      side(Grid::Dir::left, val);
    }
    
    bool interceptsWith(const RectCS other) const {
      return std::abs(c.x - other.c.x) < h.x + other.h.x &&
             std::abs(c.y - other.c.y) < h.y + other.h.y;
    }
    bool encloses(const RectCS other) const {
      return std::abs(c.x - other.c.x) <= h.x - other.h.x &&
             std::abs(c.y - other.c.y) <= h.y - other.h.y;
    }
    bool encloses(const Vector other) const {
      return std::abs(c.x - other.x) <= h.x &&
             std::abs(c.y - other.y) <= h.y;
    }
    
    union {
      Vector c;
      Vector center;
    };
    union {
      Vector h;
      Vector halfSize;
    };
  };
  
  template <typename T, Grid::Dir P_X, Grid::Dir P_Y>
  const RectCS<T, P_X, P_Y> RectCS<T, P_X, P_Y>::NEG_INF = {
    RectCS<T, P_X, P_Y>::Vector(T(0)),
    RectCS<T, P_X, P_Y>::Vector(std::numeric_limits<T>::lowest()),
  };
  
  template <typename T, Grid::Dir P_X, Grid::Dir P_Y>
  const RectCS<T, P_X, P_Y> RectCS<T, P_X, P_Y>::INF = {
    RectCS<T, P_X, P_Y>::Vector(T(0)),
    RectCS<T, P_X, P_Y>::Vector(std::numeric_limits<T>::max()),
  };
}

#endif
