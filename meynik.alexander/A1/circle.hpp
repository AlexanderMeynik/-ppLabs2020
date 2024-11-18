#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& pos, double radius);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& position) override;

  void move(const double x, const  double y) override;

  void printInfo(std::ostream& out) const override;

private:
  point_t centre_;
  double radius_;
};
#endif
