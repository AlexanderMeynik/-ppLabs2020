#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <ostream>
#include <string>

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;

  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(const point_t& position) = 0;

  virtual void move(double x, double y) = 0;

  virtual void printInfo(std::ostream& out) const = 0;

};

#endif
