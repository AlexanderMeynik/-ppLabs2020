#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <iterator>


template<class T>
void print(const T &container, const char* delimeter = " ")
{
  if(!delimeter)
  {
    delimeter = " ";
  }

  for (typename T::const_iterator temp = container.begin(); temp != container.end(); temp++)
  {
    std::cout << *temp << delimeter;
  }
}

#endif

