#include <exception>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "implementation.hpp"

int main()
{
  try
  {
    std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)),std::istream_iterator<DataStruct>());
    std::sort(vector.begin(),vector.end());
    std::copy(vector.begin(),vector.end(),std::ostream_iterator<DataStruct>(std::cout));
    return 0;
  }
  catch (std::exception & ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }
}

