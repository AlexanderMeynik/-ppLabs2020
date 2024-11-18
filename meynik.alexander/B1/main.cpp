#include <iostream>
#include <exception>
#include <string>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if(argc < 2 || argc > 4)
    {
      throw std::invalid_argument("Invalid amount of input parameters, invalid argument: " + std::to_string(argc));
    }

    std::size_t numberOfTask = std::atoi(argv[1]);

    if(numberOfTask < 1 || numberOfTask > 4)
    {
      throw:: std::invalid_argument("Invalid number of task, number of task is a number from 1 to 4 not " + std::to_string(numberOfTask) + '\n');
    }

    switch (numberOfTask)
    {
      case 1:
        if(argc != 3)
        {
          throw std::invalid_argument("Invalid amount of input parameters, amount of arguments for the task 1 must be 3 not " + std::to_string(argc) + '\n');
        }
        task1(argv[2]);
        break;
      case 2:
        if(argc != 3)
        {
          throw std::invalid_argument("Invalid amount of input parameters, amount of arguments for the task 2 must be 3 not " + std::to_string(argc) + '\n');
        }
        task2(argv[2]);
        break;
      case 3:
        if(argc != 2)
        {
          throw std::invalid_argument("Invalid amount of input parameters, amount of arguments for the task 3 must be 2 not " + std::to_string(argc) + '\n');
        }
        task3();
        break;
      case 4:
        if(argc != 4)
        {
          throw std::invalid_argument("Invalid amount of input parameters, amount of arguments for the task 4 must be 4 not " + std::to_string(argc) + '\n');
        }
        task4(argv[2], std::atoi(argv[3]));
        break;
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error\n";
    return 2;
  }
}
