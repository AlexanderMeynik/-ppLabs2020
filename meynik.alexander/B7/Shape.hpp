#ifndef LABB7_SHAPE_HPP
#define LABB7_SHAPE_HPP

#include <iostream>
class Shape
{
public:

  Shape(int x, int y);

  virtual ~Shape() = default;

  bool isMoreLeft(const Shape&anotherShape) const;

  bool isUpper(const Shape&anotherShape) const;

  virtual void draw(std::ostream&out)const=0;

protected:
  int x_;
  int y_;
};


#endif //LABB7_SHAPE_HPP
