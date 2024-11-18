#include "outputFunctor.hpp"

OutputFunctor::OutputFunctor(std::ostream & out, size_t lineWidth):
    out_(out),
    lineWidth_(lineWidth),
    outString_()
{}

OutputFunctor::~OutputFunctor()
{
  if(!outString_.empty())
  {
    out_ << outString_ << '\n';
  }
}

void OutputFunctor::operator()(Token & token)
{
  if(token.type == Type::WORD  || token.type == Type::NUMBER)
  {
    if((outString_.size() + token.line.size() + 1) > lineWidth_)
    {
      out_ << outString_ << '\n';
      outString_.clear();
    }
    else if(!outString_.empty())
    {
      outString_ += " ";
    }
    outString_ += token.line;
  }
  else
  {
    if(((token.type == Type::PUNCTUATION && token.line[1]=='-') && ((outString_.size() + 4) > lineWidth_))
       || (((outString_.size() + 1) > lineWidth_)))
    {
      size_t lastWhiteSpace = outString_.find_last_of(' ');
      size_t amountOddChars = outString_.size() - lastWhiteSpace;
      std::string temp = outString_.substr(lastWhiteSpace, amountOddChars);
      outString_.erase(lastWhiteSpace, amountOddChars);
      temp.erase(0, 1);
      out_ << outString_ << '\n';
      outString_ = temp;
    }
    if(token.type == Type::PUNCTUATION && token.line[1]=='-')
    {
      outString_ += " ";
    }
    outString_ += token.line;
  }
}
