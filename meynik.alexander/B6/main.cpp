#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include "CollectStats.hpp"

int main()
{
  try
  {

    CollectStats Stats;
    std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::ref(Stats));

    if (!std::cin.eof()&&std::cin.fail())
    {
      throw std::runtime_error("Error while reading data!");
    }

   Stats.printStats(std::cout);

   return 0;
  }
  catch (std::exception & exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem" << '\n';
    return 2;
  }

}
