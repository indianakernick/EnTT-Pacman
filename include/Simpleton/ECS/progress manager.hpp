//
//  progress manager.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_ecs_progress_manager_hpp
#define engine_ecs_progress_manager_hpp

#include <string>
#include "level.hpp"

namespace ECS {
  class ProgressManager {
  public:
    ProgressManager();
    explicit ProgressManager(const std::string &);
    ~ProgressManager();
    
    Level getIncompleteLevel() const;
    bool hasCompleted(Level) const;
    void finishLevel(Level);
    void reset();
    
    void setFilePath(const std::string &);
    void readFile();
    void writeFile();
    
  private:
    std::string filePath;
    Level numCompleted;
  };
}

#include "progress manager.inl"

#endif
