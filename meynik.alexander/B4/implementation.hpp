#ifndef LAB4_IMPLEMENTATION_HPP
#define LAB4_IMPLEMENTATION_HPP

#include <iostream>
#include <vector>

struct DataStruct {
  int key1;
  int key2;
  std::string str;
};

bool checkKey(const int key);

std::istream&expect(std::istream &in,const char C);

std::istream&operator>>(std::istream & in, DataStruct & dataStruct);

std::ostream&operator<<(std::ostream & out, const DataStruct & dataStruct);

bool operator<(const DataStruct & ldataStruct, const DataStruct & rdataStruct);

#endif

