#include "Shape.hpp"
#include <iterator>
#include <sstream>
#include <algorithm>

std::ostream&operator<< (std::ostream &out, const Shape &shape)
{
  out << shape.points.size();
  std::copy(shape.points.begin(),shape.points.end(),std::ostream_iterator<Point>(out));
  out << "\n";
  return out;
}

int squaredDistance(const Point &a, const Point &b)
{
  return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool isTriangle(const Shape& shape)
{
  return (shape.points.size() == 3);
}

bool isRectangle(const Shape& shape)
{
  if(shape.points.size() != 4)
  {
    return false;
  }

  return ((squaredDistance(shape.points[0], shape.points[2]) == squaredDistance(shape.points[0], shape.points[1])
        + squaredDistance(shape.points[1], shape.points[2]))&&(squaredDistance(shape.points[0], shape.points[2])
        == squaredDistance(shape.points[0], shape.points[3]) + squaredDistance(shape.points[3], shape.points[2])));
}

bool isSquare(const Shape& shape)
{
  if(!isRectangle(shape))
  {
    return false;
  }
  return (squaredDistance(shape.points[0],shape.points[1])==squaredDistance(shape.points[1],shape.points[2]));
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
  size_t vertices;
  in >> std::ws >> vertices;
  if (in.peek() == EOF)
  {
    return in;
  }
  if (in.fail())
  {
    return in;
  }
  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), vertices, std::back_inserter(temp));
  shape.points.swap(temp);
  if (isTriangle(shape))
  {
    shape.type = Shape::TRIANGLE;
  }
  else if (isRectangle(shape))
  {
    if (isSquare(shape))
    {
      shape.type = Shape::SQUARE;
    }
    else
    {
      shape.type = Shape::RECTANGLE;
    }
  }
  else
  {
    shape.type = Shape::OTHER;
  }
  return in;
}
