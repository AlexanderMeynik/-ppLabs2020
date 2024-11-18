#include "PhoneBookInterface.hpp"
#include <stdexcept>
#include <iostream>

static const std::string CURRENT = "current";
PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook> &&phoneBook)
{
  phoneBook_ = std::move(phoneBook);
  bookmarks_.insert(std::make_pair(CURRENT, phoneBook_->begin()));
}

void PhoneBookInterface::add(const std::string & name, const std::string & number)
{
  phoneBook_->pushBack(name,number);
  if (phoneBook_->begin() == --phoneBook_->end())
  {
    bookmarks_[CURRENT] = phoneBook_->begin();
  }
}

void PhoneBookInterface::store(const std::string &bookmark, const std::string &anotherBookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    bookmarks_.insert(std::make_pair(anotherBookmark, it->second));
    return;
  }
  std::cout << "<INVALID BOOKMARK>" << '\n';
}

void PhoneBookInterface::insertBefore(const std::string & name, const std::string & number, const std::string &bookmark)
{
  auto iter = bookmarks_.find(bookmark);
  if (iter == bookmarks_.end())
  {
    std::cout<<"<INVALID BOOKMARK>\n";
    return;
  }
  iter->second = phoneBook_->insertBefore(number, name, iter->second);
}

void PhoneBookInterface::insertAfter(const std::string & name, const std::string & number, const std::string &bookmark)
{
  auto iter = bookmarks_.find(bookmark);
  if (iter == bookmarks_.end())
  {
    std::cout<<"<INVALID BOOKMARK>\n";
    return;
  }
  iter->second = phoneBook_->insertAfter(number, name, iter->second);
}


void PhoneBookInterface::deleteBookmark(const std::string &bookmark)
{
  auto iter = bookmarks_.find(bookmark);
  if (iter == bookmarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>" << '\n';
    return;
  }
  if(iter->second == phoneBook_->end())
  {
    return;
  }
  auto deleteIt = iter->second;
  for (auto i = bookmarks_.begin(); i != bookmarks_.end(); ++i)
  {
    if (i->second == deleteIt)
    {
      if (std::next(i->second) == phoneBook_->end())
      {
        i->second = std::prev(deleteIt);
      }
      else
      {
        i->second = std::next(deleteIt);
      }
    }
  }
  phoneBook_->deleteUser(deleteIt);
}

void PhoneBookInterface::showBookmark(const std::string &bookmark)
{
  if (bookmarks_.empty())
  {
    std::cout << "<EMPTY>" << '\n';
    return;
  }
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>" << '\n';
    return;
  }
  if(it->second == phoneBook_->end())
  {
    std::cout << "<EMPTY>" << '\n';
    return;
  }
  std::cout<<*(it->second);
}

void PhoneBookInterface::moveMark(const std::string & markName, int step)
{
  auto iter = bookmarks_.find(markName);
  if (iter == bookmarks_.end())
  {
    std::cout <<"<INVALID BOOKMARK>"<<'\n';
    return;
  }
  std::advance(iter->second,step);
}

void PhoneBookInterface::moveMark(const std::string & markName, PhoneBookInterface::MoveDirection & pos)
{
  auto iter = bookmarks_.find(markName);
  if (iter == bookmarks_.end())
  {
    std::cout <<"<INVALID BOOKMARK>"<<'\n';
    return;
  }
  if (pos == MoveDirection::TO_LAST)
  {
    iter->second = std::prev(phoneBook_->end());
    return;
  }
  else if (pos == MoveDirection::TO_FIRST)
  {
    iter->second = phoneBook_->begin();
    return;
  }
}


