#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "print.hpp"

void task2(const char* fileName)
{
  std::ifstream fin (fileName);

  if(!fin.is_open())
  {
    throw std::ios_base::failure("Error while opening file: " + std::string(fileName) + "!\n");
  }

  if (fin.peek() == EOF)
  {
    return;
  }
  
  size_t capacity = 4;
  using arr_ptr = std::unique_ptr<char[], decltype(&free)>;
  arr_ptr array(static_cast<char *>(malloc(capacity)), &free);

  size_t size = 0;
  while (!fin.eof())
  {
    fin.read(&array[size], capacity - size);
    size += fin.gcount();

    if (capacity == size)
    {
      capacity = static_cast<size_t>(capacity * 1.8);
      arr_ptr arrayTemp(static_cast<char *>(realloc(array.get(), capacity)), &free);

      if (!arrayTemp)
      {
        throw std::runtime_error("Error while reallocating memory!\n");
      }
      array.release();
      std::swap(array, arrayTemp);
    }
  }

  fin.close();

  if(fin.is_open())
  {
    throw std::runtime_error("Error while closing file: " + std::string(fileName) + "!\n");
  }

  std::vector<char> outputVector(array.get(), &array[size]);
  print(outputVector, "");
}
