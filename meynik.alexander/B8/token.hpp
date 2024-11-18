#ifndef LABB8_TOKEN_HPP
#define LABB8_TOKEN_HPP

#include <string>
#include <iostream>

struct Token
{
  enum class tokenType
  {
    WORD,
    NUMBER,
    PUNCTUATION,
    EMPTY
  };
  Token(tokenType type, std::string&& str);
  tokenType type;
  std::string line;
};

#endif
