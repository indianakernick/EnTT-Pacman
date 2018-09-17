//
//  progress manager.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <fstream>

inline ECS::ProgressManager::ProgressManager()
  : filePath(),
    numCompleted() {}

inline ECS::ProgressManager::ProgressManager(const std::string &filePath)
  : filePath(filePath) {
  readFile();
}

inline ECS::ProgressManager::~ProgressManager() {
  writeFile();
}

inline ECS::Level ECS::ProgressManager::getIncompleteLevel() const {
  return numCompleted;
}

inline bool ECS::ProgressManager::hasCompleted(const Level level) const {
  return level < numCompleted;
}

inline void ECS::ProgressManager::finishLevel(const Level level) {
  if (numCompleted == level) {
    ++numCompleted;
  }
}

inline void ECS::ProgressManager::reset() {
  numCompleted = 0;
}

inline void ECS::ProgressManager::setFilePath(const std::string &newFilePath) {
  // @TODO should we only allow the user to set the path once?
  filePath = newFilePath;
}

inline void ECS::ProgressManager::readFile() {
  std::ifstream file(filePath);
  if (file.is_open()) {
    file >> numCompleted;
  } else {
    numCompleted = 0;
  }
}

inline void ECS::ProgressManager::writeFile() {
  std::ofstream file(filePath);
  if (file.is_open()) {
    file << numCompleted;
  }
}
