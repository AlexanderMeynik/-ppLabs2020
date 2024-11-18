#include <iostream>
#include <stdexcept>
#include <list>
#include <string>

template <typename T>
void print(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
{
  if (begin == end)
  {
    std::cout << "\n";
    return;
  }

  if (begin == std::prev(end))
  {
    std::cout << *begin << '\n';
    return;
  }

  std::cout << *begin << ' ' << *std::prev(end) << ' ';
  begin++;
  end--;
  print<T>(begin, end);
}

void task2()
{
  size_t amount = 0;
  int number = 0;
  std::list<int> list;
  while (std::cin >> number)
  {
    if (number < 1 || number > 20)
    {
      throw std::invalid_argument("Input number " + std::to_string(number) + " is out of range!");
    }

    ++amount;
    if (amount > 20)
    {
      throw std::invalid_argument("More than 20 numbers entered!");
    }
    list.push_back(number);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Fail with reading data!");
  }

  print<int>(list.begin(), list.end());
}
