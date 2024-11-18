#ifndef LABB8_OUTPUTFUNCTOR_HPP
#define LABB8_OUTPUTFUNCTOR_HPP

#include "token.hpp"
#include <iosfwd>
#include <string>

class OutputFunctor
{
public:

  OutputFunctor(std::ostream & out, size_t lineWidth);

  ~OutputFunctor();

  void operator()(Token & token);

private:
  using Type=Token::tokenType;
  std::ostream & out_;
  const size_t lineWidth_;
  std::string outString_;
};

#endif //LABB8_OUTPUTFUNCTOR_HPP
