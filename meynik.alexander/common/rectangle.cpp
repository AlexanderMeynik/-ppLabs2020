#include "rectangle.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

namespace meynik
{
  const double  HALF_CIRCLE = 180.0;

  Rectangle::Rectangle(const point_t& pos, const double width, const double height) :
    pos_(pos),
    width_(width),
    height_(height),
    angle_(0)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument(std::string("Width and height of rectangle must")
          + " be positive numbers!\nWidth value: " + std::to_string(width)
          + "\nHeight value: " + std::to_string(height));
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return { fabs(width_ * cos(angle_) + height_ * sin(angle_)),
        fabs(width_ * sin(angle_) + height_ * cos(angle_)), pos_ };
  }

  void Rectangle::move(const point_t& point)
  {
    pos_ = point;
  }

  void Rectangle::move(const double x, const double y)
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::printInfo(std::ostream& out) const
  {
    double angleInDegrees = (angle_ * HALF_CIRCLE)/M_PI;
    out << "Width: " << width_ << '\n' << "Height: "
        << height_ << '\n'<< "Center: ("<< pos_.x
        << ", " << pos_.y << ")\n"<<"Angle: "
        <<angleInDegrees<<'\n';
  }

  point_t Rectangle::getCentre() const noexcept
  {
    return pos_;
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive!")
          +"\nCoefficient value: " + std::to_string(coefficient)+'\n');
    }
    height_ *= coefficient;
    width_ *= coefficient;
  }

  void Rectangle::rotate(double angle)
  {
    angle_+=M_PI* angle / HALF_CIRCLE;
    angle_ = (angle_ > 0.0) ? fmod(angle_, 2 * M_PI) : 2 * M_PI + fmod(angle_, 2 * M_PI);
  }

  double Rectangle::getAngle() const noexcept
  {
    return angle_*180/M_PI;
  }
}
