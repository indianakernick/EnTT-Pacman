//
//  compose string.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_compose_string_hpp
#define engine_utils_compose_string_hpp

#include <stack>
#include <string>
#include <string_view>

namespace Utils {
  class ComposeString {
  public:
    explicit ComposeString(size_t = 4096);
    
    ///Get a pointer to the beginning of the string
    char *begin();
    ///Get a pointer to the current character ready to be written to
    char *curr();
    ///Get a pointer to the character past the end of the string
    char *end();
    ///Get a std::string_view of the composed string
    std::string_view view() const;
    ///Get the amount of free space in the allocation
    size_t freeSpace() const;
    
    ///Increase the capacity of the string
    void reserve(size_t);
    ///Increase the capacity of the string so that freeSpace is larger than the
    ///given value
    void reserveToFit(size_t);
    ///Increase the size of the string
    void addSize(size_t);
    ///Return true if the string is empty
    bool empty() const;
    
    ///Write a character to the end of the string
    void write(char);
    ///Write an array of characters to the end of the string
    void write(const char *, size_t);
    ///Write a view of characters to the end of the string
    void write(std::string_view);
    
    ///Write a number as a human-readable string
    template <typename Number>
    void writeNumber(Number);
    
    ///Write an enum given names for all enumerators
    template <typename Enum>
    void writeEnum(Enum, const std::string_view *);
    
    ///Open a pair of delimiter strings. The first string is written immediately
    ///and the second string is pushed onto a stack. The second string will be
    ///written when close is called.
    void open(const std::string &, const std::string &);
    ///Write the string stored from the cooresponding call to open
    void close();
    ///Call close until the stack of strings is empty
    void closeAll();
    
  private:
    std::unique_ptr<char []> string;
    size_t size;
    size_t capacity;
    std::stack<std::string> closingStrings;
    
    void setCapacity(size_t);
  };
}

#include "compose string.inl"

#endif
