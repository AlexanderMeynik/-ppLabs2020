#ifndef LAB3_COMMANDS_HPP
#define LAB3_COMMANDS_HPP
#include <string>
#include <iosfwd>
#include <functional>
#include <limits>
#include "PhoneBookInterface.hpp"

using FunctionType = std::function<void(PhoneBookInterface&, std::ostream&)>;

std::string parseName(std::istream& in);

std::string parseNumber(std::istream& in);

std::string parseBookmark(std::istream& in);

int getStep(const std::string & step);

FunctionType printInvalid();

FunctionType add(std::istream& in);

FunctionType store(std::istream& in);

FunctionType insert(std::istream& in);

FunctionType deleteBookmark(std::istream& in);

FunctionType showBookmark(std::istream& in);

FunctionType move(std::istream& in);

std::istream& operator >>(std::istream& in, FunctionType& function);

static const std::map<std::string, std::function<FunctionType(std::istream&)>> FUNCTIONS_TABLE =
{
  {"add", add},
  {"store", store},
  {"insert", insert},
  {"delete", deleteBookmark},
  {"show", showBookmark},
  {"move", move}
};


#endif
