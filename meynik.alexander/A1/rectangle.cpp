#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t& pos, const double width, const double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument(std::string("Width and height of rectangle must")
      +" be positive numbers.\nWidth value: "+ std::to_string(width)
      + "\nHeight value: " + std::to_string(height));
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ width_, height_, pos_ };
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
  out << "Width: " << width_ << '\n'
    << "Height: " << height_ << '\n'
    << "Center: (" << pos_.x << ", " << pos_.y << ")\n";
}
