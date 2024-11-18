#ifndef LAB3_PHONE_BOOK_INTERFACE_HPP
#define LAB3_PHONE_BOOK_INTERFACE_HPP

#include <map>
#include <string>
#include <memory>
#include "PhoneBook.hpp"

class PhoneBookInterface
{
public:

  enum class MoveDirection
  {
    TO_FIRST,
    TO_LAST
  };

  explicit PhoneBookInterface(std::unique_ptr<PhoneBook> && phoneBook);

  void add(const std::string & name, const std::string & number);

  void store(const std::string & bookmark, const std::string & anotherBookmark);

  void insertAfter(const std::string & name, const std::string & number, const std::string & bookmark);

  void insertBefore(const std::string & name, const std::string & number, const std::string & bookmark);

  void deleteBookmark(const std::string & bookmark);

  void showBookmark(const std::string & bookmark);

  void moveMark(const std::string & markName, int step);

  void moveMark(const std::string & markName, MoveDirection & pos);

private:
  std::unique_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::PhoneBookIterator> bookmarks_;
};

#endif
