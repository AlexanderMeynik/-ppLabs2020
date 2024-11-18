#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <ostream>
#include "base-types.hpp"

namespace meynik
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual void move(const point_t& position) = 0;

    virtual void move(double x, double y) = 0;

    virtual void printInfo(std::ostream& out) const = 0;

    virtual meynik::point_t getCentre() const noexcept = 0;

    virtual void scale(const double coefficient) = 0;

    virtual void rotate(double angle) = 0;

  };
}

#endif
