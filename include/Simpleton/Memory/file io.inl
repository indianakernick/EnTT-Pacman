//
//  file io.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 20/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline Memory::FileError::FileError(const char *const what)
  : std::runtime_error(what) {}

inline Memory::FileHandle Memory::openFileRead(const char *const path) {
  assert(path);
  std::FILE *const file = std::fopen(path, "rb");
  if (file == nullptr) {
    throw FileError("Failed to open file for reading");
  } else {
    return {file, {}};
  }
}

inline Memory::FileHandle Memory::openFileWrite(const char *const path) {
  assert(path);
  std::FILE *const file = std::fopen(path, "wb");
  if (file == nullptr) {
    throw FileError("Failed to open file for writing");
  } else {
    return {file, {}};
  }
}

inline Memory::FileHandle Memory::openFileRead(const std::string_view path) {
  // fopen takes a null terminated string
  static std::string temp;
  temp.reserve(path.size());
  temp.clear();
  temp.append(path.data(), path.size());
  return openFileRead(temp.c_str());
}

inline Memory::FileHandle Memory::openFileWrite(const std::string_view path) {
  // fopen takes a null terminated string
  static std::string temp;
  temp.reserve(path.size());
  temp.clear();
  temp.append(path.data(), path.size());
  return openFileWrite(temp.c_str());
}

inline size_t Memory::sizeOfFile(std::FILE *const file) {
  if (std::fseek(file, 0, SEEK_END) != 0) {
    throw FileError("Failed to seek to end of file");
  }
  const long fileSize = std::ftell(file);
  if (fileSize == long(-1)) {
    throw FileError("Failed to get size of file");
  }
  std::rewind(file);
  return fileSize;
}

inline void Memory::readFile(void *const data, const size_t size, std::FILE *const file) {
  if (std::fread(data, size, 1, file) == 0) {
    throw FileError("Failed to read from file");
  }
}

inline void Memory::writeFile(const void *const data, const size_t size, std::FILE *const file) {
  if (std::fwrite(data, size, 1, file) == 0) {
    throw FileError("Failed to write to file");
  }
  if (std::fflush(file) != 0) {
    throw FileError("Failed to flush file after writing");
  }
}

inline Memory::Buffer Memory::readFile(const std::string_view path) {
  return readFile(std::string(path));
}

inline Memory::Buffer Memory::readFile(const std::string &path) {
  return readFile(path.c_str());
}

inline Memory::Buffer Memory::readFile(const char *const path) {
  return readFile(openFileRead(path).get());
}

inline Memory::Buffer Memory::readFile(std::FILE *const file) {
  Memory::Buffer buf(sizeOfFile(file));
  readFile(buf.data(), buf.size(), file);
  return buf;
}

inline Memory::Buffer Memory::readFile(std::ifstream &stream) {
  stream.seekg(0, std::ios::end);
  Memory::Buffer buf(stream.tellg());
  stream.seekg(0, std::ios::beg);
  stream.read(buf.data<std::ifstream::char_type>(), buf.size());
  if (stream.good()) {
    return buf;
  } else {
    throw FileError("Failed to read from input stream");
  }
}

inline void Memory::writeFile(const Memory::Buffer &buf, const std::string_view path) {
  writeFile(buf, std::string(path));
}

inline void Memory::writeFile(const Memory::Buffer &buf, const std::string &path) {
  writeFile(buf, path.c_str());
}

inline void Memory::writeFile(const Memory::Buffer &buf, const char *const path) {
  writeFile(buf, openFileWrite(path).get());
}

inline void Memory::writeFile(const Memory::Buffer &buf, std::FILE *const file) {
  if (std::fwrite(buf.data(), buf.size(), 1, file) == 0) {
    throw FileError("Failed to write to file");
  }
  if (std::fflush(file) != 0) {
    throw FileError("Failed to flush file after writing");
  }
}

inline void Memory::writeFile(const Memory::Buffer &buf, std::ofstream &stream) {
  stream.write(buf.data<std::ofstream::char_type>(), buf.size<std::streamsize>());
  stream.flush();
  if (!stream.good()) {
    throw FileError("Failed to write to output stream");
  }
}
