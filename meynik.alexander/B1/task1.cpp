#include <iostream>
#include <forward_list>
#include "sort.hpp"
#include "print.hpp"

void task1(char* direction)
{
  std::function<bool(double, double)> compare = getDirection<double>(direction);
  std::vector<int> inputVector;

  int inputVar;
  while(std::cin >> inputVar)
  {
    inputVector.push_back(inputVar);
  }

  if(!std::cin.eof() && !std::cin.eof())
  {
    throw std::runtime_error("Error while read!\n");
  }

  if (inputVector.empty())
  {
    return;
  }

  std::vector<int> indexVector = inputVector;
  sort<IndexAccess>(indexVector, compare);
  print(indexVector);
  std::cout<<'\n';

  std::vector<int> atVector = inputVector;
  sort<AtAccess>(atVector, compare);
  print(atVector);
  std::cout<<'\n';

  std::forward_list<int> list(inputVector.begin(), inputVector.end());
  sort<IteratorAccess>(list, compare);
  print(list);
  std::cout<<'\n';
}
