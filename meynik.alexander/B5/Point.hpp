#ifndef LAB5_POINT_HPP
#define LAB5_POINT_HPP

#include <iostream>

struct Point
{
  int x, y;
};

std::istream&skipSpaces(std::istream& in);

std::istream&expect(std::istream &in, char C);

std::istream&operator>>(std::istream&in,Point&point);

std::ostream&operator<<(std::ostream&out,const Point&point);


#endif
