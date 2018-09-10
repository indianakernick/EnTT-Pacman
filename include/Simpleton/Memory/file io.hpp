//
//  file io.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 20/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_file_io_hpp
#define engine_memory_file_io_hpp

#include <cstdio>
#include <string>
#include <fstream>
#include "buffer.hpp"
#include <string_view>

namespace Memory {
  class FileError final : public std::runtime_error {
  public:
    explicit FileError(const char *);
  };
  
  struct FileCloser {
    void operator()(std::FILE *const file) const noexcept {
      std::fclose(file);
    }
  };

  using FileHandle = std::unique_ptr<std::FILE, FileCloser>;
  
  static_assert(sizeof(FileHandle) == sizeof(std::FILE *));

  FileHandle openFileRead(const char *);
  FileHandle openFileWrite(const char *);
  
  FileHandle openFileRead(std::string_view);
  FileHandle openFileWrite(std::string_view);

  size_t sizeOfFile(std::FILE *);
  
  void readFile(void *, size_t, std::FILE *);
  void writeFile(const void *, size_t, std::FILE *);

  Buffer readFile(std::string_view);
  Buffer readFile(const std::string &);
  Buffer readFile(const char *);
  Buffer readFile(std::FILE *);
  Buffer readFile(std::ifstream &);
  
  void writeFile(const Buffer &, std::string_view);
  void writeFile(const Buffer &, const std::string &);
  void writeFile(const Buffer &, const char *);
  void writeFile(const Buffer &, std::FILE *);
  void writeFile(const Buffer &, std::ofstream &);
}

#include "file io.inl"

#endif
