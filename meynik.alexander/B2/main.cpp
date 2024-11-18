#include <iostream>
#include <stdexcept>
#include "tasks.hpp"


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of argc!");
    }

    int task = atoi(argv[1]);

    switch(task)
    {
      case 1:
      {
        task1();
        break;
      }
      case 2:
      {
        task2();
        break;
      }
      default:
      {
        throw std::invalid_argument("Invalid task number!");
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!\n";
    return 2;
  }

  return 0;
}
