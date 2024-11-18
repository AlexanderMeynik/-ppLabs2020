#ifndef LABB7_TRIANGLE_HPP
#define LABB7_TRIANGLE_HPP

#include "Shape.hpp"
#include <iostream>

class Triangle:public Shape
{
public:
  Triangle(int x, int y);
  void draw(std::ostream&out) const override;
};


#endif //LABB7_TRIANGLE_HPP
