#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include <string>

namespace meynik
{
  Circle::Circle(const point_t& pos, double radius) :
    centre_(pos),
    radius_(radius)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument(std::string("Radius of circle must be positive!\n")
          + "Radius value:" + std::to_string(radius));
    }
  }

  double Circle::getArea() const noexcept
  {
    return M_PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{ radius_ * 2, radius_ * 2, centre_ };
  }

  void Circle::move(const point_t& point)
  {
    centre_ = point;
  }

  void Circle::move(const double x, const double y)
  {
    centre_.x += x;
    centre_.y += y;
  }

  void Circle::printInfo(std::ostream& out) const
  {
    out << "Radius: " << radius_ << "\nCenter: ("<< centre_.x 
        << ", " << centre_.y << ")\n";
  }

  point_t Circle::getCentre() const noexcept
  {
    return centre_;
  }

  void Circle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive!")
          + "\nCoefficient value: " + std::to_string(coefficient) + '\n');
    }
    radius_ *= coefficient;
  }

  void Circle::rotate(double)
  {
  }
}
