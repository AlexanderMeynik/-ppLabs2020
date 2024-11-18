#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include "print.hpp"
#include "sort.hpp"

void fillRandom(double* array, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Array size can't be less or equal to zero!\n");
  }

  if(!array)
  {
    throw std::invalid_argument("Array pointer can't be the null pointer!\n");
  }

  std::uniform_real_distribution<double> distribution(-1, 1);
  std::default_random_engine gen(time(0));

  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(gen);
  }
}

void task4(char* direction, const int size)
{
  std::function<bool(double, double)> compare = getDirection<double>(direction);

  if (size <= 0)
  {
    throw std::invalid_argument("Vector size can't be less or equal to zero!\n");
  }

  std::vector<double> vector(size);

  fillRandom(vector.data(), size);

  print(vector);
  std::cout << '\n';

  sort<IndexAccess>(vector, compare);
  print(vector);
}
