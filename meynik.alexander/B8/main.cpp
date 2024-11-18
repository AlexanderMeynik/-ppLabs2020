#include <exception>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include "inputIterator.hpp"
#include "outputFunctor.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if ((argc != 1) && (argc != 3))
    {
      throw std::invalid_argument("Invalid number of arguments!");
    }
    int lineWidth = 40;
    if(argv[1] != nullptr)
    {
      if(strcmp(argv[1], "--line-width") != 0)
      {
        throw std::invalid_argument("Invalid format of args!");
      }
      lineWidth = atoi(argv[2]);
      if(lineWidth < 25)
      {
        throw std::invalid_argument("Invalid line width!");
      }
    }

    OutputFunctor functor(std::cout, static_cast<size_t>(lineWidth));
    std::for_each(InputIterator(std::cin), InputIterator(), std::ref(functor));
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown problem\n";
    return 2;
  }
}
