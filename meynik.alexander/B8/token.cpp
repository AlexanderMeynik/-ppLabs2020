#include "token.hpp"

Token::Token(tokenType type, std::string&& str) :
    type(type),
    line(std::move(str))
{}
