#ifndef LABB8_INPUTITERATOR_HPP
#define LABB8_INPUTITERATOR_HPP

#include <iterator>
#include <iosfwd>
#include "token.hpp"

class InputIterator : public std::iterator<std::input_iterator_tag, Token>
{
public:
  explicit InputIterator(std::istream & in);

  InputIterator();

  Token& operator*();

  Token* operator->();

  InputIterator & operator++();

  InputIterator &  operator++(int);

  bool operator== (const InputIterator& it) const;

  bool operator!= (const InputIterator& it) const;

private:

  void read();

  void readNumber();

  void readWord();

  void readDash();

  using Type = Token::tokenType;
  std::istream * in_;
  bool hasInputStream_;
  Token token_;
};

#endif //LABB8_INPUTITERATOR_HPP
