#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace meynik
{
  class CompositeShape : Shape
  {
  public:
    CompositeShape() noexcept;

    CompositeShape(const size_t capacity_);
    
    ~CompositeShape() = default;

    CompositeShape(const CompositeShape& array);

    CompositeShape(CompositeShape&& array) noexcept;

    std::shared_ptr<Shape>& operator[](size_t index) const;

    CompositeShape& operator=(const CompositeShape& array);

    CompositeShape& operator=(CompositeShape&& array) noexcept;

    void insertShape(std::shared_ptr<Shape>& shape);

    void printInfo(std::ostream& out) const override;

    void deleteShape(size_t index);

    double getArea() const noexcept override;

    point_t getCentre() const noexcept override;

    size_t getSize() const noexcept;

    size_t getCapacity() const noexcept;

    rectangle_t getFrameRect() const noexcept override;
    
    Matrix getMatrix() const;

    void move(const double x, const double y) noexcept override;

    void move(const point_t& center) noexcept override;

    void scale(const double coefficient) override;

    void rotate(double angle) override;

  private:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t size_;
    size_t capacity_;
    arrayPtr array_;
  };
}

#endif
