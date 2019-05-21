//
//  live stats.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_live_stats_hpp
#define engine_math_live_stats_hpp

#include <limits>

namespace Math {
  template <typename DataPoint>
  class LiveStats {
  public:
    static constexpr DataPoint DEFAULT_MIN = std::numeric_limits<DataPoint>::max();
    static constexpr DataPoint DEFAULT_MAX = std::numeric_limits<DataPoint>::lowest();
  
    LiveStats() = default;
  
    void update(const DataPoint dataPoint) {
      if (dataPoint < min) {
        min = dataPoint;
      }
      if (dataPoint > max) {
        max = dataPoint;
      }
      sum += dataPoint;
      ++count;
    }
    void update(const DataPoint *const dataPoints, const size_t numDataPoints) {
      const DataPoint *const end = dataPoints + numDataPoints;
      for (const DataPoint *d = dataPoints; d != end; ++d) {
        update(*d);
      }
    }
    
    DataPoint getAvg(const DataPoint defaultAvg = 0) const {
      if (count == 0) {
        return defaultAvg;
      } else {
        return sum / count;
      }
    }
    DataPoint getMin() const {
      return min;
    }
    DataPoint getMax() const {
      return max;
    }
    
    void resetAvg() {
      count = 0;
      sum = 0;
    }
    void resetMin() {
      min = DEFAULT_MIN;
    }
    void resetMax() {
      max = DEFAULT_MAX;
    }
    
    void resetAll() {
      resetAvg();
      resetMin();
      resetMax();
    }
  
  private:
    size_t count = 0;
    DataPoint sum = 0;
    DataPoint min = DEFAULT_MIN;
    DataPoint max = DEFAULT_MAX;
  };
}

#endif
