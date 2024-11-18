#include <iostream>
#include <stdexcept>
#include <sstream>
#include "queueWithPriority.hpp"
#include "commands.hpp"

void task1()
{
  std::string currectLine;
  QueueWithPriority<std::string> queue;

  while(getline(std::cin, currectLine))
  {
    if(!std::cin.good() && !std::cin.eof())
    {
      throw std::ios_base::failure("Fail while reading data!");
    }

    std::stringstream sin(currectLine);
    std::string command;
    sin >> command;
    if(command == "add")
    {
      add(queue, sin, std::cout);
    }
    else if(command == "get")
    {
      get(queue, std::cout);
    }
    else if(command == "accelerate")
    {
      accelerate(queue);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }

  }
}
