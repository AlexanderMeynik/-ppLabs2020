#include "Square.hpp"

void Square::draw(std::ostream &out) const
{
  out<<"SQUARE ("<<x_<<"; "<<y_<<")\n";
}

Square::Square(int x, int y) :
    Shape(x, y)
{}
