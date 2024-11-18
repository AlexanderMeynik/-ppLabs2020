#ifndef LAB3_PHONE_BOOK_HPP
#define LAB3_PHONE_BOOK_HPP

#include <string>
#include <list>


class PhoneBook
{
public:
  struct PhoneBookElement
  {
    std::string number;
    std::string name;
  };

  friend std::ostream&operator<<(std::ostream&out,const PhoneBookElement&el);

  using PhoneBookIterator = std::list<PhoneBookElement>::iterator;

  PhoneBookIterator insertAfter(const std::string & name, const std::string & number, PhoneBookIterator iterator);

  PhoneBookIterator insertBefore(const std::string & name, const std::string & number, PhoneBookIterator iterator);

  void pushBack(const std::string & name, const std::string & number);

  PhoneBookIterator deleteUser(PhoneBookIterator iterator);

  PhoneBookIterator begin();

  PhoneBookIterator end();

private:
  std::list<PhoneBookElement> container_;
};


#endif
