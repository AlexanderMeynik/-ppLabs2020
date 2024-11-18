#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace meynik
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& pos, double radius);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& position) override;

    void move(const double x, const  double y) override;

    void printInfo(std::ostream& out) const override;
  
    point_t getCentre() const noexcept override;

    void scale(const double coefficient) override;

    void rotate(double angle) override;

  private:
    point_t centre_;
    double radius_;
  };
}

#endif
