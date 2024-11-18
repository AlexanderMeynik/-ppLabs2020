#include "PhoneBook.hpp"
#include <stdexcept>
#include <iostream>

std::ostream &operator<<(std::ostream &out, const PhoneBook::PhoneBookElement &el)
{
  out << el.name << ' ' << el.number << "\n";
  return out;
}
void PhoneBook::pushBack(const std::string & name, const std::string & number)
{
  container_.push_back({name,number});
}

PhoneBook::PhoneBookIterator PhoneBook::deleteUser(PhoneBookIterator iterator)
{
  if(container_.empty())
  {
    return container_.end();
  }
  return container_.erase(iterator);
}

PhoneBook::PhoneBookIterator PhoneBook::insertBefore(const std::string & name, const std::string & number, PhoneBookIterator iterator)
{
  return container_.insert(iterator, PhoneBook::PhoneBookElement{number, name});
}

PhoneBook::PhoneBookIterator PhoneBook::insertAfter(const std::string & name, const std::string & number, PhoneBookIterator iterator)
{
  return container_.insert(++iterator, PhoneBook::PhoneBookElement{number, name});
}

PhoneBook::PhoneBookIterator PhoneBook::begin()
{
  return container_.begin();
}

PhoneBook::PhoneBookIterator PhoneBook::end()
{
  return container_.end();
}
