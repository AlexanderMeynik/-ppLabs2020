#include "Circle.hpp"

void Circle::draw(std::ostream&out) const
{
  out<<"CIRCLE ("<<x_<<"; "<<y_<<")\n";
}

Circle::Circle(int x, int y) :
    Shape(x, y)
{}
