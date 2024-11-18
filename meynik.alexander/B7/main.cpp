#include <exception>
#include <iostream>
#include "tasks.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if (argc!=2)
    {
      throw std::invalid_argument("Invalid count of args!");
    }

    int taskNumber = atoi(argv[1]);

    switch (taskNumber)
    {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        throw std::invalid_argument("Invalid task number");
    }
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown problem\n";
    return 2;
  }
}
