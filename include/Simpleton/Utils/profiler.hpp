//
//  profiler.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 12/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_profiler_hpp
#define engine_utils_profiler_hpp

#ifdef ENABLE_PROFILER

#include <chrono>
#include <cstdio>
#include <unordered_map>

namespace Utils {
  class Profiler {
  public:
    explicit Profiler(const char *name);
    ~Profiler();
    
    static void formatInfo(std::FILE *);
    static void resetInfo();
    
  private:
    struct TreeNode {
      uint64_t calls = 0;
      uint64_t time = 0;
      std::unordered_map<const char *, TreeNode> children;
      const char *name;
      TreeNode *parent;
    };
    
    std::chrono::high_resolution_clock::time_point start;
    static TreeNode *current;
    static TreeNode tree;
    
    static void recFormatInfo(std::FILE *, TreeNode *, int);
    
    static const int NAME_INDENT = 2;
    static const int MAX_DEPTH = 16;
    static const int NUM_PREC = 4;
    static const int NAME_WIDTH = 48;
    static const int REST_WIDTH = 24;
    
    static char spaces[NAME_INDENT * MAX_DEPTH];
    static bool initSpaces;
    static bool oddLine;
  };
}

//macros are weird!
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define PROFILE(name) Utils::Profiler CONCAT(profiler_, __COUNTER__) {#name}
#define PROFILER_INFO(stream) Utils::Profiler::formatInfo(stream)

#include "profiler.inl"

#else

#define PROFILE(name)
#define PROFILER_INFO(stream)

#endif

#endif
