#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <functional>

void task1()
{
  std::transform((std::istream_iterator<float>(std::cin)), std::istream_iterator<float>(),
      std::ostream_iterator<float>(std::cout,"\n"),
          std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1) );
  if(std::cin.fail()&&!std::cin.eof())
  {
    throw std::invalid_argument("Error while reading data!");
  }
}
