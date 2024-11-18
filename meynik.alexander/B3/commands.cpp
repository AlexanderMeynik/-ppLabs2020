#include "commands.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <algorithm>

std::string parseName(std::istream& in)
{
  std::string name;
  in >> name;
  if (!in.eof())
  {
    std::string temp;
    std::getline(in, temp);
    name += temp;
  }
  if (name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string::iterator iter = std::remove(name.begin(), name.end(), '\\');
  name.erase(iter, name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

std::string parseNumber(std::istream& in)
{
  std::string number;
  in >> number;
  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  for (char i : number)
  {
    if (!isdigit(i))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return number;
}

std::string parseBookmark(std::istream& in)
{
  std::string bookmark;
  in >> bookmark;
  if (bookmark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  for (char i : bookmark)
  {
    if ((!isalnum(i)) && (i != '-'))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return bookmark;
}

int getStep(const std::string & step)
{
  auto it=step.begin();
  if(step[0]=='+'||step[0]=='-')
  {
    it++;
  }
  for(;it<step.end();it++)
  {
    if(!isdigit(*it))
    {
      throw std::invalid_argument("");
    }
  }
  return std::stoi(step);
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> printInvalid()
{
  return [](PhoneBookInterface&, std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
  };
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> add(std::istream& in)
{
  std::string number = parseNumber(in);
  std::string name = parseName(in);
  return [name, number](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.add(name, number);
  };
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> store(std::istream& in)
{

  std::string bookmark = parseBookmark(in);
  std::string anotherBookmark = parseBookmark(in);
  return [bookmark, anotherBookmark](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.store(bookmark, anotherBookmark);
  };
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> insert(std::istream& in)
{
  std::string position, bookmark, number, name;
  in >> position;
  bookmark = parseBookmark(in);
  number = parseNumber(in);
  name = parseName(in);

  if (position == "before")
  {
    return [number, name, bookmark](PhoneBookInterface& phoneBook, std::ostream&)
    {
      phoneBook.insertBefore(name, number, bookmark);
    };
  }
  else if (position == "after")
  {
    return [number, name, bookmark](PhoneBookInterface& phoneBook, std::ostream&)
    {
      phoneBook.insertAfter(name, number, bookmark);
    };
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> deleteBookmark(std::istream& in)
{
  std::string bookmark = parseBookmark(in);
  return [bookmark](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.deleteBookmark(bookmark);
  };
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> showBookmark(std::istream& in)
{
  std::string bookmark = parseBookmark(in);
  return [bookmark](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.showBookmark(bookmark);
  };
}

std::function<void(PhoneBookInterface& phoneBook, std::ostream& out)> move(std::istream& in)
{
  std::string bookmark = parseBookmark(in);
  std::string step;
  in >> step;
  return [step, bookmark](PhoneBookInterface& phoneBook, std::ostream& out)
  {
    if(step == "last" || step == "first")
    {
      auto direction = (step == "last") ? PhoneBookInterface::MoveDirection::TO_LAST:PhoneBookInterface::MoveDirection::TO_FIRST;
      phoneBook.moveMark(bookmark, direction);
    }
    else
    {
      int offset;
      try
      {
        offset = getStep(const_cast<std::string &>(step));
      }
      catch(std::invalid_argument & ex)
      {
        out << "<INVALID STEP>" << '\n';
        return;
      }
      phoneBook.moveMark(bookmark, offset);
    }
  };
}

std::istream& operator >>(std::istream& in, FunctionType& function)
{
  try
  {
    std::string command;
    in >> command;

    auto iter =  FUNCTIONS_TABLE.find(command);

    if(iter == FUNCTIONS_TABLE.end())
    {
      function = printInvalid();
      return in;
    }
    function = (*iter).second(in);
  }
  catch (std::invalid_argument& err)
  {
    if(char(in.unget().peek()) != '\n')
    {
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    function = printInvalid();
  }
  return in;
}
