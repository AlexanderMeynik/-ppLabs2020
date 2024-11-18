#include <iostream>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include "PhoneBookInterface.hpp"
#include "commands.hpp"

void task1()
{
  PhoneBook book;
  PhoneBookInterface bookInterface(std::make_unique<PhoneBook>(book));
  std::for_each(std::istream_iterator<FunctionType>(std::cin),std::istream_iterator<FunctionType>(),
      [&](auto& function)
      {
        function(bookInterface, std::cout);
      });
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 1");
  }
}
