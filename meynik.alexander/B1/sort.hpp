#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <vector>
#include <cstring>
#include <stdexcept>

#include "access.hpp"

template<typename T>
std::function<bool(T,T)> getDirection(const char* direction)
{
  if(strcmp(direction, "ascending") == 0)
  {
    return std::greater<T>();
  }
  if(strcmp(direction, "descending") == 0)
  {
    return std::less<T>();
  }
  throw std::invalid_argument(std::string(direction) + " is not right direction for sort!\n");;
}

template < template < typename > class Access, typename ContainerType>
void sort (ContainerType & data, std::function<bool(typename ContainerType::value_type, typename ContainerType::value_type)> compare)
{

  typedef Access< ContainerType > access;
  const auto begin = access::begin(data);
  const auto end = access::end(data);

  for(auto i = begin; i != end; i++)
  {
    for(auto j = access::next(i); j != end; j++)
    {
      if(compare(access::element(data, i), access::element(data, j)))
      {
        std::swap(access::element(data, i), access::element(data, j));
      }
    }
  }
}

#endif
