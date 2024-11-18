#include "Shape.hpp"

bool Shape::isMoreLeft(const Shape &anotherShape) const
{
  return (x_<anotherShape.x_);
}

bool Shape::isUpper(const Shape &anotherShape) const
{
  return (y_>anotherShape.y_);
}

Shape::Shape(int x, int y):
    x_(x),
    y_(y)
{}
