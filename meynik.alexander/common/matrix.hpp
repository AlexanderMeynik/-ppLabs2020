#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include <memory>
#include <iostream>
#include "shape.hpp"

namespace meynik
{
  class Matrix
  {
  public:

    using shapePtr = std::shared_ptr<Shape>;

    class Layer
    {
    public:
      friend class Matrix;

      shapePtr& operator[](size_t column);

    private:
      Layer(shapePtr* shapes, size_t size);

      shapePtr* shapes_;
      size_t size_;
    };

    Matrix();

    Matrix(const Matrix& anotherMatrix);

    Matrix(Matrix&& anotherMatrix) noexcept;
    
    ~Matrix() = default;

    Matrix& operator=(const Matrix& anotherMatrix);

    Matrix& operator=(Matrix&& anotherMatrix) noexcept;

    Matrix::Layer operator[](const size_t row);

    void addShape(const std::shared_ptr<Shape>&shape);

    size_t getAmountOfRows()const noexcept;

    size_t getAmountOfColoumns()const noexcept;

    void printInfo(std::ostream& out) const noexcept;

  private:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t rows_;
    size_t columns_;
    arrayPtr matrix_;

    bool areShapesIntersected(const std::shared_ptr<Shape>& firstShape,const std::shared_ptr<Shape>& secondShape) const noexcept;
    
  };
}

#endif
