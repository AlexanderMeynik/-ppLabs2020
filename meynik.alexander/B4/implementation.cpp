#include "implementation.hpp"
#include <sstream>

const char COMMA=',';

bool checkKey(const int key)
{
  return (abs(key)<=5);
}

std::istream&expect(std::istream &in,const char C)
{
  if ((in >> std::ws).peek() == C)
  {
    in.ignore();
  }
  else
  {
    throw std::invalid_argument("Invalid input");
  }
  return in;
}
std::istream&operator>>(std::istream & in, DataStruct & dataStruct)
{
  std::string line;
  if (!getline(in, line))
  {
    return in;
  }
  std::istringstream istr(line);
  int key1,key2;
  std::string str;
  istr>> key1;
  expect(istr,COMMA);
  istr>> key2;
  expect(istr,COMMA);
  getline(istr,str);
  if (istr.fail() && !istr.eof())
  {
    throw std::runtime_error("Error while reading data!");
  }
  if(!checkKey(key1)||!checkKey(key2)||str.empty())
  {
    throw std::invalid_argument("Invalid data!");
  }
  dataStruct.key1=key1;
  dataStruct.key2=key2;
  dataStruct.str=std::move(str);
  return in;
}

std::ostream&operator<<(std::ostream & out, const DataStruct & dataStruct)
{
  out << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << '\n';
  return out;
}

bool operator<(const DataStruct & ldataStruct, const DataStruct & rdataStruct)
{
  if (ldataStruct.key1 == rdataStruct.key1)
  {
    if (ldataStruct.key2 == rdataStruct.key2)
    {
      return ldataStruct.str.length() < rdataStruct.str.length();
    }
    return ldataStruct.key2 < rdataStruct.key2;
  }
  return ldataStruct.key1 < rdataStruct.key1;
}
