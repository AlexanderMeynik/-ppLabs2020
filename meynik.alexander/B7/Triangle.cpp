#include "Triangle.hpp"
void Triangle::draw(std::ostream&out) const
{
  out<<"TRIANGLE ("<<x_<<"; "<<y_<<")\n";
}

Triangle::Triangle(int x, int y) :
    Shape(x, y)
{}
