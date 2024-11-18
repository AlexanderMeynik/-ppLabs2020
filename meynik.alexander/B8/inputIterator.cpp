#include "inputIterator.hpp"

const size_t MAX_WORD_LENGTH = 20;

InputIterator::InputIterator(std::istream &in) :
    in_(&in),
    hasInputStream_(true),
    token_(Token::tokenType::EMPTY, "")
{
  read();
}

InputIterator::InputIterator() :
    in_(nullptr),
    hasInputStream_(false),
    token_(Token::tokenType::EMPTY, "")
{}


Token &InputIterator::operator*()
{
  return token_;
}

Token *InputIterator::operator->()
{
  return &token_;
}

InputIterator & InputIterator::operator++()
{
  read();
  return *this;
}

InputIterator & InputIterator::operator++(int)
{
  InputIterator * returnValue = this;
  read();
  return *returnValue;
}

bool InputIterator::operator==(const InputIterator &it) const
{
  return (hasInputStream_ == it.hasInputStream_) && (!hasInputStream_ || in_ == it.in_);
}

bool InputIterator::operator!=(const InputIterator &it) const
{
  return !(operator==(it));
}

void InputIterator::read()
{
  (*in_) >> std::ws;
  char first = static_cast<char>(in_->get());
  char second = static_cast<char>(in_->peek());
  
  if ((*in_).fail())
  {
    hasInputStream_ = false;
    return;
  }

  if (isalpha(first))
  {
    in_->unget();
    readWord();
  }
  else if (isdigit(first) || ((first == '-' || first == '+') && isdigit(second)))
  {
    in_->unget();
    readNumber();
  }
  else if (std::ispunct(first))
  {
    if (token_.line.empty())
    {
      throw std::invalid_argument("Text starts with the punctuation!");
    }
    if (token_.type == Type::PUNCTUATION)
    {
      if (token_.line == "," && first == '-')
      {
        in_->unget();
        readDash();
        return;
      }
      else
      {
        throw std::invalid_argument("Two or more punctuations in a row!");
      }
    }
    if (first == '-')
    {
      in_->unget();
      readDash();
    }
    else
    {
      std::string temp;
      temp.push_back(first);
      token_ = std::move(Token(Type::PUNCTUATION, std::move(temp)));
    }
  }
}

void InputIterator::readNumber()
{
  std::string number;
  size_t amountOfDots = 0;
  number.push_back(static_cast<char>(in_->get()));
  while (isdigit(in_->peek()) || in_->peek() == '.')
  {
    if (number.length() >= MAX_WORD_LENGTH)
    {
      throw std::invalid_argument("Invalid number length!");
    }
    char ch = static_cast<char>(in_->get());
    if (ch == '.')
    {
      ++amountOfDots;
      if (amountOfDots > 1)
      {
        throw std::invalid_argument("Two or more dots in number!");
      }
    }
    number.push_back(ch);
  }
  token_ = std::move(Token(Type::NUMBER, std::move(number)));
}

void InputIterator::readWord()
{
  std::string word;
  word.push_back(static_cast<char>(in_->get()));
  while (isalpha(in_->peek()) || in_->peek() == '-')
  {
    char character = static_cast<char>(in_->get());
    if (word.length() >= MAX_WORD_LENGTH)
    {
      throw std::invalid_argument("Invalid word length!");
    }
    if (character == '-' && in_->peek() == '-')
    {
      throw std::invalid_argument("Amount of \"-\" symbols in word can't be more than 2!");
    }
    word.push_back(character);
  }
  token_ = std::move(Token(Type::WORD, std::move(word)));
}

void InputIterator::readDash()
{
  size_t symbolCount = 0;
  while (in_->peek() == '-')
  {
    in_->get();
    ++symbolCount;
  }
  if (symbolCount != 3)
  {
    throw std::invalid_argument("Invalid amount of \"-\" symbols in dash!");
  }
  token_ = std::move(Token(Type::PUNCTUATION, "---"));
}


