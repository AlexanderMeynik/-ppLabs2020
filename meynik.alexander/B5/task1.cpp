#include "tasks.hpp"
#include <unordered_set>
#include <iterator>

void task1()
{
  std::unordered_set<std::string> words((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());
  if(std::cin.fail()&&!std::cin.eof())
  {
    throw std::invalid_argument("Error while reading data!");
  }
  if(words.empty())
  {
    return;
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
