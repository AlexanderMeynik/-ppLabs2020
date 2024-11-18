#ifndef LABB7_CIRCLE_HPP
#define LABB7_CIRCLE_HPP

#include "Shape.hpp"
#include <iostream>

class Circle:public Shape
{
public:
  Circle(int x, int y);
  void draw(std::ostream&out) const override;
};

#endif //LABB7_CIRCLE_HPP
