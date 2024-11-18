#ifndef LAB5_SHAPE_HPP
#define LAB5_SHAPE_HPP

#include "Point.hpp"
#include <vector>

struct Shape
{
  enum ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    OTHER
  };
  std::vector<Point> points;
  ShapeType type;
};

std::ostream&operator<< (std::ostream &out, const Shape &shape);

std::istream&operator>> (std::istream &in, Shape &shape);

int squaredDistance(const Point & a, const Point & b);

bool isTriangle(const Shape& shape);

bool isRectangle(const Shape& shape);

bool isSquare(const Shape& shape);

#endif
