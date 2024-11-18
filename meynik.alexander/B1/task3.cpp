#include <iostream>
#include <vector>
#include "print.hpp"

void task3()
{
  std::vector<int> vector;

  int inputVar;
  while(std::cin >> inputVar)
  {
    if(inputVar == 0)
    {
      break;
    }
    vector.push_back(inputVar);
  }

  if(!std::cin.good() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading input value!\n");
  }

  if(vector.empty())
  {
    return;
  }

  if(inputVar != 0)
  {
    throw std::invalid_argument("Last number must be zero, not " + std::to_string(inputVar) + '\n');
  }

  auto lastElement = vector.back();

  if(lastElement == 1)
  {
    auto i = vector.begin();
    while(i < vector.end())
    {
      if(*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        i++;
      }
    }
  }
  else if (lastElement == 2)
  {
    auto i = vector.begin();
    while(i < vector.end())
    {
      if(*i % 3 == 0)
      {
        i++;
        i = vector.insert(i, 3, 1);
        i += 3;
      }
      else
      {
        i++;
      }
    }
  }

  print(vector);
}
