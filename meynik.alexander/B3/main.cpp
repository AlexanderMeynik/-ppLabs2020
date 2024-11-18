#include <iostream>
#include <string>
#include "tasks.hpp"
int main(int argc, char * argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Amount of arguments must be equal to 2, not "+ std::to_string(argc));
    }

    int part = atoi(argv[1]);

    if (part == 1)
    {
      task1();
    }
    else if (part == 2)
    {
      task2();
    }
    else
    {
      throw std::invalid_argument("Invalid task number!");
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
