//
//  freq limiter.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 21/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_time_freq_limiter_hpp
#define engine_time_freq_limiter_hpp

#include "get.hpp"

namespace Time {
  class OpPerSec {};
  class Frequency {};
  
  constexpr OpPerSec OP_PER_SEC {};
  constexpr Frequency FREQUENCY {};

  ///Limits the frequency of some operation in real-time
  template <typename Duration>
  class RealFreqLimiter {
  public:
    RealFreqLimiter()
      : period(0),
        lastDo(getPoint<Duration>()) {}
    template <typename Int>
    explicit RealFreqLimiter(const Int count)
      : period(count),
        lastDo(getPoint<Duration>() - period) {}
    template <typename Int>
    RealFreqLimiter(Frequency, const Int count)
      : period(1.0f / static_cast<float>(count)),
        lastDo(getPoint<Duration>() - period) {}
    template <typename Int>
    RealFreqLimiter(OpPerSec, const Int count)
      : period((static_cast<float>(Duration::period::num * count) / Duration::period::den)),
        lastDo(getPoint<Duration>() - period) {}
    ~RealFreqLimiter() = default;
    
    ///Change the period
    void setPeriod(const Duration newPeriod) {
      period = newPeriod;
    }
    
    ///Get the period
    Duration getPeriod() const {
      return period;
    }
    
    ///Get the amount of time that has passes since the last operation
    Duration getTimeSinceLast() const {
      return getPoint<Duration>() - lastDo;
    }
    
    ///Get the progress of the cycle
    template <typename Float>
    std::enable_if_t<
      std::is_floating_point<Float>::value,
      Float
    >
    getProgress() const {
      return static_cast<Float>((getPoint<Duration>() - lastDo).count()) / period.count();
    }
    
    ///Simulate a fake operation
    void reset() {
      lastDo = getPoint<Duration>();
    }
    
    ///Ensure that canDo will return true
    void willDo() {
      lastDo = getPoint<Duration>() - period;
    }
    
    ///If this function returns true, it will not return true again until the
    ///period has passed
    bool canDo() {
      const Point<Duration> now = getPoint<Duration>();
      if (now - lastDo >= period) {
        lastDo = now;
        return true;
      } else {
        return false;
      }
    }
    
    ///Similar to canDo but...
    bool canDoOverlap() {
      const Point<Duration> now = getPoint<Duration>();
      if (now - lastDo >= period) {
        lastDo += period;
        return true;
      } else {
        return false;
      }
    }
    
    using CountType = uint32_t;
    
    ///Returns the number of times the operation can be performed
    CountType canDoMultiple() {
      return canDoMultipleImpl<false>();
    }
    
    ///Similar to canDoMultiple but...
    CountType canDoMultipleOverlap() {
      return canDoMultipleImpl<true>();
    }
    
  private:
    //minumum period between operations
    Duration period;
    //time of last operation
    Point<Duration> lastDo;
    
    template <bool OVERLAP>
    CountType canDoMultipleImpl() {
      const Point<Duration> now = getPoint<Duration>();
      
      if (period == 0) {
        if (now - lastDo == Duration(0)) {
          return 0;
        } else {
          return std::numeric_limits<CountType>::max();
        }
      }
    
      CountType count = 0;
      while (now - lastDo >= period) {
        lastDo += period;
        ++count;
      }
      if constexpr (!OVERLAP) {
        lastDo = now;
      }
      return count;
    }
  };
  
  ///Limits the frequency of some operation in delta-time
  template <typename Number>
  class DeltaFreqLimiter {
    
    static_assert(std::is_arithmetic<Number>::value);
  
  public:
    DeltaFreqLimiter()
      : period(0) {}
    explicit DeltaFreqLimiter(const Number period)
      : period(period) {}
    DeltaFreqLimiter(Frequency, const Number frequency)
      : period(Number(1) / frequency) {}
    ~DeltaFreqLimiter() = default;
    
    ///Change the period
    void setPeriod(const Number newPeriod) {
      period = newPeriod;
    }
    ///Get the period
    Number getPeriod() const {
      return period;
    }
    
    ///Change the frequency
    void setFrequency(const Number newFreq) {
      period = Number(1) / newFreq;
    }
    ///Get the frequency
    Number getFrequency() const {
      return Number(1) / period;
    }
    
    ///Get the amount of time that has passes since the last operation
    Number getTimeSinceLast() const {
      return timeSinceLast;
    }
    
    ///Get the progress of the cycle
    template <typename Float>
    std::enable_if_t<
      std::is_floating_point<Float>::value,
      Float
    >
    getProgress() const {
      return static_cast<Float>(timeSinceLast) / period;
    }
    
    ///Advance time forward
    void advance(const Number delta) {
      timeSinceLast += delta;
    }
    
    ///Simulate a fake operation
    void reset() {
      timeSinceLast = 0;
    }
    
    ///Ensure that canDo will return true
    void willDo() {
      timeSinceLast = period;
    }
    
    ///If this function returns true, it will not return true again until the
    ///period has passed
    bool canDo() {
      if (timeSinceLast >= period) {
        timeSinceLast = Number(0);
        return true;
      } else {
        return false;
      }
    }
    
    ///Similar to canDo but there are no gaps between periods
    bool canDoOverlap() {
      if (timeSinceLast >= period) {
        timeSinceLast -= period;
        return true;
      } else {
        return false;
      }
    }
    
    using CountType = uint32_t;
    
    ///Returns the number of times the operation can be performed
    CountType canDoMultiple() {
      return canDoMultipleImpl<false>();
    }
    
    ///Similar to canDoMultiple but there are no gaps between periods
    CountType canDoMultipleOverlap() {
      return canDoMultipleImpl<true>();
    }
    
  private:
    //minumum period between operations
    Number period;
    //time since last operation
    Number timeSinceLast = Number(0);
    
    template <bool OVERLAP>
    CountType canDoMultipleImpl() {
      if (period == Number(0)) {
        if (timeSinceLast == Number(0)) {
          return Number(0);
        } else {
          return std::numeric_limits<CountType>::max();
        }
      }
      CountType count = 0;
      while (timeSinceLast >= period) {
        timeSinceLast -= period;
        ++count;
      }
      if constexpr (!OVERLAP) {
        timeSinceLast = Number(0);
      }
      return count;
    }
  };
}

#endif
