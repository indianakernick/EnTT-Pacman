//
//  compose string.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_compose_string_hpp
#define engine_utils_compose_string_hpp

#include <vector>
#include <memory>
#include <string>
#include <string_view>

namespace Utils {
  class ComposeString {
  public:
    explicit ComposeString(size_t = 4096);
    
    /// Get a pointer to the beginning of the string
    const char *data() const;
    /// Get the size of the string
    size_t size() const;
    /// Get a pointer to the beginning of the string
    char *begin();
    /// Get a pointer to the current character ready to be written to
    char *curr();
    /// Get a pointer to the character past the end of the string
    char *end();
    /// Get a std::string_view of the composed string
    std::string_view view() const;
    /// Get the amount of free space in the allocation
    size_t freeSpace() const;
    
    /// Increase the capacity of the string
    void reserve(size_t);
    /// Increase the capacity of the string so that freeSpace is larger than the
    /// given value
    void reserveToFit(size_t);
    /// Increase the size of the string
    void addSize(size_t);
    /// Return true if the string is empty
    bool empty() const;
    
    /// Write a character to the end of the string
    void write(char);
    /// Write a view of characters to the end of the string
    void write(std::string_view);
    /// Write a string literal to the end of the string
    template <size_t Size>
    void write(const char (&)[Size]);
    
    /// Write a number as a human-readable string
    template <typename Number>
    void writeNumber(Number);
    
    /// Write an enum given names for all enumerators
    template <typename Enum>
    void writeEnum(Enum, const std::string_view *);
    
    /// Open a separated list and write a string
    template <typename String>
    void open(String &&);
    /// Open a separated list
    void open();
    
    /// Write the separtor for a separated list. This should be called before
    /// writing the list item
    template <typename String>
    void separate(String &&);
    /// Return true if a separator should be written. This should be called
    /// before writing the list item
    bool separate();
    
    /// Close a separated list and write a string
    template <typename String>
    void close(String &&);
    /// Close a separated list
    void close();
    
  private:
    std::unique_ptr<char []> string;
    size_t length;
    size_t capacity;
    std::vector<bool> sepStack;
    
    void setCapacity(size_t);
  };
  
  /// Initialize at the beginning of the loop. Use to determine whether to write
  /// a separator for a separated list. Faster but less convenient than the
  /// ComposeString API
  class Separator {
  public:
    /// Returns true if the separator should be written. Call this at the
    /// beginning of the loop
    explicit operator bool() {
      return std::exchange(write, true);
    }
  
  private:
    bool write = false;
  };
  
  /*
   
  str.open('{');
  for (int i : ints) {
    str.separate(", ");
    str.write(i);
  }
  str.close('}');
 
  str.write('{');
  Utils::Separator sep;
  for (int i : ints) {
    if (sep) str.write(", ");
    str.write(i);
  }
  str.write('}');
 
  str.write('{');
  bool write = false;
  for (int i : ints) {
    if (std::exchange(write, true)) {
      str.write(", ");
    }
    str.write(i);
  }
  str.write('}');
 
  */
}

#include "compose string.inl"

#endif
