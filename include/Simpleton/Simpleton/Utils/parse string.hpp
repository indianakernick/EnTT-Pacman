//
//  parse string.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_parse_string_hpp
#define engine_utils_parse_string_hpp

#include <string>
#include <string_view>
#include "line col.hpp"
#include <system_error>

namespace Utils {
  /// An error related to parsing with a Utils::ParseString
  class ParsingError : public std::exception {
  public:
    explicit ParsingError(LineCol<>);
    
    LineCol<>::Line line() const;
    LineCol<>::Col column() const;
  
  protected:
    const LineCol<>::Line mLine;
    const LineCol<>::Col mCol;
  };

  ///A character was expected but not present
  class ExpectChar final : public ParsingError {
  public:
    ExpectChar(char, LineCol<>);
  
    char expectedChar() const;
    
    const char *what() const noexcept override;
    
  private:
    char mExpected;
  };
  
  /// A string stored on the stack
  template <size_t Size>
  class StackString {
  public:
    explicit StackString(std::string_view);
    
    std::string_view view() const;
  
  private:
    char data[Size];
    size_t size;
  };
  
  ///A sequence of characters was expected but not present
  class ExpectString final : public ParsingError {
  public:
    ExpectString(std::string_view, LineCol<>);
    
    std::string_view expectedStr() const;
    
    const char *what() const noexcept override;
  
  private:
    StackString<64> expected;
  };
  
  ///Unable to interpret characters as a number
  class InvalidNumber final : public ParsingError {
  public:
    InvalidNumber(std::errc, LineCol<>);
  
    std::errc error() const;
  
    const char *what() const noexcept override;
  
  private:
    std::errc mError;
  };
  
  ///Unable to interpret characters as an enumeration
  class InvalidEnum final : public ParsingError {
  public:
    InvalidEnum(std::string_view, LineCol<>);
    
    std::string_view name() const;
    
    const char *what() const noexcept override;
  
  private:
    StackString<64> nameStr;
  };

  ///A view onto a string being parsed
  class ParseString {
  public:
    explicit ParseString(const std::string &);
    explicit ParseString(std::string_view);
    ParseString(const char *, size_t);
    
    ///Get a pointer to the string being parsed. This pointer is incremented
    ///as the string is parsed.
    const char *data() const;
    ///Get the size of the string that has not been parsed yet. This number
    ///is decremented as the string is parsed.
    size_t size() const;
    ///Get the line and column position of the string yet to be parsed
    ///relative to the beginning.
    LineCol<> lineCol() const;
    ///Get the line
    LineCol<>::Line line() const;
    ///Get the column
    LineCol<>::Col col() const;
    ///Get a std::string_view of the unparsed string
    std::string_view view() const;
    ///Get a std::string_view of the unparsed string no larger than the size
    ///provided. Returned size may be less than requested size to avoid
    ///running off the end of the string.
    std::string_view view(size_t) const;
    
    ///Return true if the string is empty
    bool empty() const;
    ///Get a character on the string. Does not do range checking
    char operator[](size_t) const;
    ///Get a character on the string. Does range checking
    char at(size_t) const;
    ///Get the first character. Does not check the size of the string
    char front() const;
    
    ///Move the front of the string forward. Increments line and column
    ///numbers accordingly
    ParseString &advance(size_t);
    ///Move the front of the string forward by one character. Increments line
    ///and column numbers accordingly
    ParseString &advance();
    
    ///Move the front forward while the front is equal to the supplied character
    ParseString &skip(char);
    ///Move the front forward while the supplied predicate returns true
    template <typename Pred>
    ParseString &skip(Pred &&);
    ///Move the front forward while the front is whitespace
    ParseString &skipWhitespace();
    
    ///Move the front forward until the front is equal to the supplied character
    ParseString &skipUntil(char);
    ///Move the front forward until the supplied predicate returns true
    template <typename Pred>
    ParseString &skipUntil(Pred &&);
    ///Move the front forward until the front is whitespace
    ParseString &skipUntilWhitespace();
    
    ///Throw a ExpectChar exception if the front character is not equal to the
    ///supplied character
    ParseString &expect(char);
    ///Throw a ExpectString exception if the front part of the string is not
    ///equal to the supplied string
    ParseString &expect(const char *, size_t);
    ///Throw a ExpectString exception if the front part of the string is not
    ///equal to the supplied string
    ParseString &expect(std::string_view);
    
    ///Throw a ExpectChar exception if the front character is not equal to the
    ///supplied character after all characters that satisfy the supplied
    ///predicate have been skipped.
    template <typename Pred>
    ParseString &expectAfter(char, Pred &&);
    ///Throw a ExpectChar exception if the front character is not equal to the
    ///supplied character after all whitespace characters have been skipped
    ParseString &expectAfterWhitespace(char);
    
    ///Advances and returns true if the front character is equal to the supplied
    ///character. Does nothing and returns false otherwise
    bool check(char);
    ///Advances and returns true if the front part of the string is equal to the
    ///supplied string. Does nothing and returns false otherwise
    bool check(const char *, size_t);
    ///Advances and returns true if the front part of the string is equal to the
    ///supplied string. Does nothing and returns false otherwise
    bool check(std::string_view);
    ///Advances and returns true if the front part of the string is equal to the
    ///supplied string. Does nothing and returns false otherwise
    template <size_t SIZE>
    bool check(const char (&)[SIZE]);
    ///Advances and returns true if the supplied predicate returns true for the
    ///first character. Does nothing and returns false otherwise
    template <typename Pred>
    bool check(Pred &&);
    
    ///Advances and returns true if the front character is equal to any of the
    ///supplied characters
    bool checkAnyChar(const char *, size_t);
    ///Advances and returns true if the front character is equal to any of the
    ///supplied characters
    bool checkAnyChar(std::string_view);
    
    ///Interprets the front part of the string as a number. Returns a
    ///positive error code on failure
    template <typename Number>
    std::errc tryParseNumber(Number &);
    ///Interprets the front part of the string as a number. Throws an
    ///InvalidNumber exception on failure
    template <typename Number>
    ParseString &parseNumber(Number &);
    ///Interprets the front part of the string as a number. Throws an
    ///InvalidNumber exception on failure
    template <typename Number>
    Number parseNumber();
    
    ///Interprets the front part of the string as an enum. Returns the index of
    ///a name that matches or returns the number of names if no name matches.
    size_t tryParseEnum(const std::string_view *, size_t);
    ///Interprets the front part of the string as an enum. Returns an enum with
    ///the matched name or throws a InvalidEnum exception if no name matches.
    template <typename Enum>
    Enum parseEnum(const std::string_view *, size_t);
    
    ///Interprets the front part of the string as an enum followed by a
    ///character for which the predicate returns true. Returns the index of
    ///a name that matches or returns the number of names if no name matches.
    template <typename Pred>
    size_t tryParseEnum(const std::string_view *, size_t, Pred &&);
    ///Interprets the front part of the string as an enum followed by a
    ///character for which the predicate returns true. Returns an enum with
    ///the matched name or throws a InvalidEnum exception if no name matches.
    template <typename Enum, typename Pred>
    Enum parseEnum(const std::string_view *, size_t, Pred &&);
    
    ///Copies characters from the front part of the string. Advances the number
    ///of characters that were copied.
    size_t copy(char *, size_t);
    ///Copies characters from the front part of the string. Advances the number
    ///of characters that were copied.
    ParseString &copy(std::string &, size_t);
    
    ///Copies characters from the front part of the string while the supplied
    ///predicate returns true. Advances the number of characters that
    ///were copied.
    template <typename Pred>
    size_t copyWhile(char *, size_t, Pred &&);
    ///Copies characters from the front part of the string while the supplied
    ///predicate returns true. Advances the number of characters that
    ///were copied.
    template <typename Pred>
    ParseString &copyWhile(std::string &, Pred &&);
    
    ///Copies characters from the front part of the string until the front is
    ///equal to the supplied character. Advances the number of characters that
    ///were copied.
    size_t copyUntil(char *, size_t, char);
    ///Copies characters from the front part of the string until the front is
    ///equal to the supplied character. Advances the number of characters that
    ///were copied.
    ParseString &copyUntil(std::string &, char);
    
    ///Copies characters from the front part of the string until the supplied
    ///predicate returns true. Advances the number of characters that
    ///were copied.
    template <typename Pred>
    size_t copyUntil(char *, size_t, Pred &&);
    ///Copies characters from the front part of the string until the supplied
    ///predicate returns true. Advances the number of characters that
    ///were copied.
    template <typename Pred>
    ParseString &copyUntil(std::string &, Pred &&);
    
    ///Copies characters from the front part of the string until the front is
    ///whitespace. Advances the number of characters that were copied.
    size_t copyUntilWhitespace(char *, size_t);
    ///Copies characters from the front part of the string until the front is
    ///whitespace. Advances the number of characters that were copied.
    ParseString &copyUntilWhitespace(std::string &);
    
    ///Creates a std::string_view that views the front of the string with a
    ///size of 0
    std::string_view beginViewing() const;
    ///Modify a std::string_view to view a region of the string between the
    ///call to beginViewing and the current position (not including the current
    ///character)
    void endViewing(std::string_view &) const;
    
  private:
    const char *beg;
    const char *end;
    LineCol<> pos;
    
    //Advance without range checks
    void advanceNoCheck(size_t);
    void advanceNoCheck();
    size_t minSize(size_t) const;
  };
}

#include "parse string.inl"

#endif
