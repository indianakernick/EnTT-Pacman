//
//  benchmark.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_time_benchmark_hpp
#define engine_time_benchmark_hpp

#include <chrono>
#include <iostream>

#define TIME_BENCHMARK(NAME, ...)                                               \
  {                                                                             \
    std::cout << #NAME;                                                         \
    using Clock = std::chrono::high_resolution_clock;                           \
    using NanoDuration = std::chrono::duration<uintmax_t, std::nano>;           \
    const Clock::time_point startTime = Clock::now();                           \
    {                                                                           \
      __VA_ARGS__                                                               \
    }                                                                           \
    const Clock::time_point endTime = Clock::now();                             \
    const NanoDuration duration = endTime - startTime;                          \
    std::cout << "  \t" << (duration.count() / 1E6L) << "ms\n";                 \
  }

#endif
