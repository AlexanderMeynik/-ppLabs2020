#include "composite-shape.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

namespace meynik
{
  const double  HALF_CIRCLE = 180.0;

  CompositeShape::CompositeShape() noexcept :
    size_(0),
    capacity_(0),
    array_(nullptr)
  {}

  CompositeShape::CompositeShape(const size_t capacity_) :
    size_(0),
    capacity_(capacity_),
    array_(new std::shared_ptr<Shape>[capacity_])
  {}

  CompositeShape::CompositeShape(const CompositeShape& array) :
    size_(array.size_),
    capacity_(array.capacity_),
    array_(new std::shared_ptr<Shape>[array.capacity_])
  {
    for (size_t i = 0; i < size_; i++)
    {
      array_[i] = array.array_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape&& array) noexcept :
    size_(array.size_),
    capacity_(array.capacity_),
    array_(std::move(array.array_))
  {
    array.size_ = 0;
    array.array_.reset();
    array.capacity_ = 0;
  }

  std::shared_ptr<Shape>& CompositeShape::operator[](size_t index) const
  {
    if (size_ == 0 || index > (size_ - 1))
    {
      throw std::out_of_range(std::string("CompositeShape index out of range!Index value: ")
          + std::to_string(index) + '\n');
    }
    return array_[index];
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& array)
  {
    if (&array == this)
    {
      return *this;
    }
    arrayPtr temp;
    temp.reset(new std::shared_ptr<Shape>[array.capacity_]);
    for (size_t i = 0; i < array.size_; i++)
    {
      temp[i] = array.array_[i];
    }
    size_ = array.size_;
    capacity_ = array.capacity_;
    array_ = std::move(temp);
    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& array) noexcept
  {
    if (&array == this)
    {
      return *this;
    }
    size_ = array.size_;
    capacity_ = array.capacity_;
    array_ = std::move(array.array_);
    array.size_ = 0;
    array.capacity_ = 0;
    array.array_ = nullptr;
    return *this;
  }

  void CompositeShape::insertShape(std::shared_ptr<Shape>& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Attempt to insert empty shape pointer!");
    }
    if (capacity_ == 0)
    {
      arrayPtr temp;
      temp.reset(new std::shared_ptr<Shape>[1]);
      capacity_ = 1;
      array_ = std::move(temp);
    }
    if (capacity_ == size_)
    {
      const int coefficient = 2;
      arrayPtr temp(new std::shared_ptr<Shape>[capacity_ * coefficient]);
      for (size_t i = 0; i < size_; i++)
      {
        temp[i] = array_[i];
      }
      capacity_ *= coefficient;
      array_ = std::move(temp);
    }
    array_[size_] = shape;
    size_++;
  }

  void CompositeShape::printInfo(std::ostream& out) const
  {
    for (size_t i = 0; i < size_; i++)
    {
      out << "Element with " << i << " index:\n";
      array_[i]->printInfo(out);
      out << '\n';
    }
    out << '\n';
  }

  void CompositeShape::deleteShape(size_t index)
  {
    if (size_ == 0 || index > (size_ - 1))
    {
      throw std::out_of_range(std::string("Index of deleting shape lies beyong the limits")
          + " of composite shape!" + "Index value:" + std::to_string(index) + '\n');
    }
    for (size_t i = index; i < (size_ - 1); i++)
    {
      array_[i] = array_[i + 1];
    }
    array_[size_ - 1] = nullptr;
    --size_;
  }

  double CompositeShape::getArea() const noexcept
  {
    double comp_area = 0;
    for (size_t i = 0; i < size_; i++)
    {
      comp_area += array_[i]->getArea();
    }
    return comp_area;
  }

  point_t CompositeShape::getCentre() const noexcept
  {
    return getFrameRect().pos;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return rectangle_t{ 0.0, 0.0, {0.0, 0.0} };
    }
    rectangle_t frame = array_[0]->getFrameRect();
    double leftSide = frame.pos.x - frame.width / 2;
    double rightSide = frame.pos.x + frame.width / 2;
    double topSide = frame.pos.y + frame.height / 2;
    double lowerSide = frame.pos.y - frame.height / 2;
    for (size_t i = 1; i < size_; i++)
    {
      frame = array_[i]->getFrameRect();
      if ((frame.pos.x - frame.width / 2) < leftSide)
      {
        leftSide = frame.pos.x - frame.width / 2;
      }
      if ((frame.pos.x + frame.width / 2) > rightSide)
      {
        rightSide = frame.pos.x + frame.width / 2;
      }
      if ((frame.pos.y + frame.height / 2) > topSide)
      {
        topSide = frame.pos.y + frame.height / 2;
      }
      if ((frame.pos.y - frame.height / 2) < lowerSide)
      {
        lowerSide = frame.pos.y - frame.height / 2;
      }
    }
    return { (rightSide - leftSide), (topSide - lowerSide), {(leftSide + (rightSide - leftSide) / 2), (lowerSide + (topSide - lowerSide) / 2)} };
  }

  Matrix CompositeShape::getMatrix() const
  {
    Matrix temp;
    for (size_t i = 0; i < size_; i++)
    {
      temp.addShape(array_[i]);
    }
    return temp;
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      array_[i]->move(x, y);
    }
  }

  void CompositeShape::move(const point_t& center) noexcept
  {
    this->move(center.x - this->getFrameRect().pos.x, center.y - this->getFrameRect().pos.y);
  }

  void CompositeShape::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive!")
          + "\nCoefficient value: " + std::to_string(coefficient) + '\n');
    }
    const point_t centre = getCentre();
    point_t shapeCentre;
    for (size_t i = 0; i < size_; i++)
    {
      array_[i]->scale(coefficient);
      shapeCentre = array_[i]->getFrameRect().pos;
      array_[i]->move((shapeCentre.x - centre.x) * (coefficient - 1), (shapeCentre.y - centre.y) * (coefficient - 1));
    }
  }

  void CompositeShape::rotate(double angle)
  {
    double angleInRad = M_PI * angle / HALF_CIRCLE;
    angleInRad = (angleInRad > 0.0) ? fmod(angleInRad, 2 * M_PI) : 2 * M_PI + fmod(angleInRad, 2 * M_PI);
    point_t centre = getCentre();
    for (size_t i = 0; i < size_; i++)
    {
      double deltaX = array_[i]->getCentre().x - centre.x;
      double deltaY = array_[i]->getCentre().y - centre.y;
      const double newX = centre.x + (deltaX * (cos(angleInRad))) - (deltaY * (sin(angleInRad)));
      const double newY = centre.y + (deltaX * (sin(angleInRad))) + (deltaY * (cos(angleInRad)));
      array_[i]->move({ newX, newY });
      array_[i]->rotate(angle);
    }
  }

  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  size_t CompositeShape::getCapacity() const noexcept
  {
    return capacity_;
  }

}
