#include <iostream>
#include <algorithm>
#include "factorial.hpp"

void task2()
{
  Factorial container;
  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";
  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
}
