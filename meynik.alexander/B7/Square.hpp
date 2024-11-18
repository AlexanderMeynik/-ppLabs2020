#ifndef LABB7_SQUARE_HPP
#define LABB7_SQUARE_HPP

#include "Shape.hpp"
#include <iostream>

class Square:public Shape
{
public:
  Square(int x, int y);
  void draw(std::ostream&out) const override;
};


#endif //LABB7_SQUARE_HPP
