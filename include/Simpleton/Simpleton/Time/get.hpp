//
//  get.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 14/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_time_get_hpp
#define engine_time_get_hpp

#include <chrono>
#include <ctime>
#include <string>

namespace Time {
  using Rep = typename std::chrono::nanoseconds::rep;

  ///Get the current time as a number
  template <typename Duration>
  typename Duration::rep get() {
    return std::chrono::duration_cast<Duration>(
      std::chrono::high_resolution_clock::now()
      .time_since_epoch()
    )
    .count();
  }
  
  ///Get the current time as a number
  template <typename Rep, typename Period>
  Rep get() {
    return get<std::chrono::duration<Rep, Period>>();
  }
  
  template <typename Duration>
  using Point = std::chrono::time_point<std::chrono::high_resolution_clock, Duration>;
  
  ///Get the current time as a std::chrono::time_point
  template <typename Duration>
  Point<Duration> getPoint() {
    return std::chrono::time_point_cast<Duration>(
      std::chrono::high_resolution_clock::now()
    );
  }
  
  ///Get the current time as a std::chrono::duration since epoch
  template <typename Duration>
  Duration getDuration() {
    return std::chrono::duration_cast<Duration>(
      std::chrono::high_resolution_clock::now()
      .time_since_epoch()
    );
  }
  
  ///Get the Unix timestamp
  inline Rep getDate() {
    return std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now()
      .time_since_epoch()
    )
    .count();
  }
  
  ///Get the formatted date as Www Mmm dd hh:mm:ss yyyy
  inline std::string getDateStr() {
    std::time_t now = std::time(nullptr);
    return std::ctime(&now);
  }
  
  ///Get the formatted time as hh:mm:ss
  inline std::string getTimeStr() {
    std::string out(8, ' ');
    std::time_t now = std::time(nullptr);
    std::strftime(const_cast<char *>(out.c_str()), 9, "%T", std::localtime(&now));
    return out;
  }
};

#endif
